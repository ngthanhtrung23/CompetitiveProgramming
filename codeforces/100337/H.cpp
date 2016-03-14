#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define SZ(x) ((int) (x).size())
using namespace std;

int n;
struct R {
    int x1, y1, x2, y2;

    void read() {
        cin >> x1 >> y1 >> x2 >> y2;
        assert(x1 <= x2);
        assert(y1 <= y2);
    }
} a[60111];

void print(double x) {
    cout << (fixed) << setprecision(1) << (x);
}

struct Event {
    int x, y1, y2, d;

    Event() {}
    Event(int x, int y1, int y2, int d) : x(x), y1(y1), y2(y2), d(d) {}
};
bool operator < (const Event& a, const Event& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.d < b.d;
}

int savex, savey;

bool intersect(pair<int,int>&a, pair<int,int>&b) {
    if (a.second < b.first) return false;
    if (b.second < a.first) return false;
    return true;
}

bool check(int val) {
    vector<Event> events;
    FOR(i,1,n) {
        int x1 = a[i].x1;
        int x2 = a[i].x2 - val;

        int y1 = a[i].y1;
        int y2 = a[i].y2 - val;

        if (x1 <= x2 && y1 <= y2) {
            events.push_back(Event(x1, y1, y2, -1));
            events.push_back(Event(x2, y1, y2, +1));
        }
    }
    sort(events.begin(), events.end());

    multiset< pair<int,int> > all;
    for(auto e : events) {
        pair<int,int> p = make_pair(e.y1, e.y2);
        if (e.d == -1) {
            auto it = all.lower_bound(make_pair(e.y1, -1000111000));
            if (it != all.end()) {
                auto q = *it;
                if (intersect(p, q)) {
                    savex = e.x;
                    savey = min(p.second, q.second);
                    return true;
                }
            }
            if (it != all.begin()) {
                --it;
                auto q = *it;
                if (intersect(p, q)) {
                    savex = e.x;
                    savey = min(p.second, q.second);
                    return true;
                }
            }
            all.insert(p);
        }
        else {
            all.erase(all.find(p));
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) a[i].read();

        int l = 0, r = 400000, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        check(res);

        if (res == 0) cout << "Impossible" << endl;
        else {
            print(savex + res / 2.0); cout << ' ';
            print(savey + res / 2.0); cout << ' ';
            print(res / 2.0);
            cout << endl;
        }
    }
}
