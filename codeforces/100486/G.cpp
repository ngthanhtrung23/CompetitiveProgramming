#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define SZ(x) ((int) (x).size())
#define ll long long
using namespace std;

const int MN = 90111;

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
} a[MN];
int n;

struct Line {
    Point A, B;
    int id;
} l[MN];

int ccw(const Point& a, Point b, Point c) {
    b = b - a;
    c = c - a;
    ll t = b.x*c.y - b.y*c.x;

    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

bool operator < (const Point& a, const Point& b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}
bool operator == (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator <= (const Point& a, const Point& b) {
    return a < b || a == b;
}

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((b) < (a)) ? (a) : (b))

bool order(const Point&a, const Point&b, const Point&c) {
    return a < b && b < c;
}

int cntIntersect(Line u, Line v) {
    if (ccw(u.A, u.B, v.A) == 0
            && ccw(u.A, u.B, v.B) == 0) {
        // 4 points are collinear
        if (u.B <= v.A || v.B <= u.A) return 0;
        return 1;
    }

    if (ccw(u.A, u.B, v.A) == 0 && order(u.A, v.A, u.B)) return 1;
    if (ccw(u.A, u.B, v.B) == 0 && order(u.A, v.B, u.B)) return 1;
    if (ccw(v.A, v.B, u.A) == 0 && order(v.A, u.A, v.B)) return 1;
    if (ccw(v.A, v.B, u.B) == 0 && order(v.A, u.B, v.B)) return 1;

    if (ccw(u.A, u.B, v.A) * ccw(u.A, u.B, v.B) < 0
            && ccw(v.A, v.B, u.A) * ccw(v.A, v.B, u.B) < 0) {
        return 1;
    }
    return 0;
}

int mark[MN];
double get (int i, double cx) {
    if (a[i].x == a[i + 1].x) return (a[i].y + a[i + 1].y) / 2.0;
    return a[i].y + (a[i + 1].y - a[i].y) / (a[i + 1].x - a[i].x + 0.0) * (cx - a[i].x);
}

struct comp {
    bool operator() (const int& i, const int& j) const {
        double x1 = max (min (a[i].x, a[i + 1].x), min (a[j].x, a[j + 1].x));
        double x2 = min (max (a[i].x, a[i + 1].x), max (a[j].x, a[j + 1].x));
        double cx = (x1 + x2) / 2;
        double a = get (i, cx);
        double b = get (j, cx);
        return a < b - 1e-6 || (abs (a - b) < 1e-6 && i < j);
    }   
};
int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1 && n) {
        map<Point,int> cnt;
        FOR(i,1,n) {
            int x, y; scanf("%d%d", &x, &y);
            a[i].x = x;
            a[i].y = y;

            cnt[a[i]] += 1;
        }
        a[n+1] = a[1];
        FOR(i,1,n) {
            l[i].A = a[i];
            l[i].B = a[i+1];
            l[i].id = i;

            if (l[i].B < l[i].A) swap(l[i].A, l[i].B);
        }

        bool intersect = false;
        for(auto p : cnt) {
            if (p.second > 1) {
                intersect = true;
                break;
            }
        }
        if (!intersect) {
            vector< pair< pair<ll,int>, int > > events;
            FOR(i,1,n) {
                ll l = min(a[i].x, a[i+1].x);
                ll r = max(a[i].x, a[i+1].x);
                events.push_back(make_pair(make_pair(l, 0), i));
                events.push_back(make_pair(make_pair(r, 1), i));
            }
            sort(events.begin(), events.end());

            FOR(i,1,n) mark[i] = false;

            set<int, comp> all;
            for(auto p : events) {
                int id = p.second;
                if (!mark[id]) all.insert(id);

                auto it = all.find(id);
                auto prev = it;
                if (prev != all.begin()) {
                    prev--;
                    if (cntIntersect(l[id], l[*prev])) {
                        intersect = true;
                        break;
                    }
                }
                auto next = it; ++next;
                if (next != all.end()) {
                    if (cntIntersect(l[id], l[*next])) {
                        intersect = true;
                        break;
                    }
                    if (cntIntersect(l[*prev], l[*next])) {
                        intersect = true;
                        break;
                    }
                }
                if (mark[id]) all.erase(id);
                mark[id] = !mark[id];
            }
        }
        cout << (intersect ? "NO" : "YES") << endl;
    }
}
