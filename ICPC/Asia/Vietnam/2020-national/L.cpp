#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

struct Point {
    int x, y;
};
bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// Implement (union by size) + (path compression)
// Reference:
// Zvi Galil and Giuseppe F. Italiano,
// Data structures and algorithms for disjoint set union problems
struct Dsu {
  public:
    Dsu() : _n(0) {}
    Dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

const int ADD = -1;
const int QUERY = 0;
const int REMOVE = +1;

struct Event {
    int typ;

    int x;
    int y1, y2;
};
bool operator < (const Event& a, const Event& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.typ != b.typ) return a.typ < b.typ;
    if (a.y1 != b.y1) return a.y1 < b.y1;
    return a.y2 < b.y2;
}

bool solve(const vector<Point>& points) {
    if (SZ(points) <= 2) return false;

    map<Point, int> idOf;
    REP(i,SZ(points)) {
        idOf[points[i]] = i;
    }

    map<int, vector< pair<int,int> >> xToIds, yToIds;
    REP(i,SZ(points)) {
        int x = points[i].x;
        int y = points[i].y;
        xToIds[x].push_back({y, i});
        yToIds[y].push_back({x, i});
    }

    Dsu dsu(SZ(points));
    vector<Event> events;

    // For each X, there are even number of points.
    for (auto [x, ids] : xToIds) {
        if (SZ(ids) % 2 != 0) {
            return false;
        }
        sort(ALL(ids));

        for (int i = 0; i < SZ(ids); i += 2) {
            int u = ids[i].second;
            int v = ids[i + 1].second;

            dsu.merge(u, v);
            events.push_back({
                QUERY,
                x,
                points[u].y,
                points[v].y,
            });
        }
    }

    // For each Y, there are even number of points.
    for (auto [y, ids] : yToIds) {
        if (SZ(ids) % 2 != 0) {
            return false;
        }
        sort(ALL(ids));

        for (int i = 0; i < SZ(ids); i += 2) {
            int u = ids[i].second;
            int v = ids[i + 1].second;

            dsu.merge(u, v);
            events.push_back({
                ADD,
                points[u].x,
                y,
                -1,
            });
            events.push_back({
                REMOVE,
                points[v].x,
                y,
                -1,
            });
        }
    }

    // Only 1 connected component.
    if (dsu.size(0) != SZ(points)) {
        return false;
    }

    // Check no intersection.
    sort(ALL(events));
    // no need for multiset, as horizontal segments don't intersect.
    set<int> current_ys;
    for (const auto& event : events) {
        if (event.typ == ADD) {
            assert(!current_ys.count(event.y1));
            current_ys.insert(event.y1);
        } else if (event.typ == REMOVE) {
            assert(current_ys.count(event.y1));
            current_ys.erase(event.y1);
        } else {
            auto it = current_ys.upper_bound(event.y1);
            if (it != current_ys.end() && *it < event.y2) {
                return false;
            }
        }
    }

    return true;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n; cin >> n;
        vector<Point> points(n);
        for (auto& point : points) {
            cin >> point.x >> point.y;
        }
        cout << (solve(points) ? "YES" : "NO") << '\n';
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
