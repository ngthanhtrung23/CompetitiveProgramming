#include <bits/stdc++.h>
#define int long long
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
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        x1 *= 2;
        x2 *= 2;
        y1 *= 2;
        y2 *= 2;
    }
} a[60111];

void print(int x) {
    cout << (fixed) << setprecision(1) << (x / 2.0);
}

const int MV = 1000111;
vector< pair<int,int> > open[MV], close[MV];
int savex, savey;

bool intersect(pair<int,int>&a, pair<int,int>&b) {
    if (a.second < b.first) return false;
    if (b.second < a.first) return false;
    return true;
}

bool check(int val) {
    REP(i,MV) {
        open[i].clear();
        close[i].clear();
    }
    FOR(i,1,n) {
        int x1 = a[i].x1 + val;
        int x2 = a[i].x2 - val;
        int y1 = a[i].y1 + val;
        int y2 = a[i].y2 - val;

        if (x1 <= x2 && y1 <= y2) {
            open[x1].push_back(make_pair(y1, y2));
            close[x2].push_back(make_pair(y1, y2));
        }
    }
    multiset< pair<int,int> > all;
    REP(col,MV) {
        for(auto p : open[col]) {
            auto it = all.lower_bound(make_pair(p.first, 0));
            if (it != all.end()) {
                auto q = *it;
                if (intersect(p, q)) {
                    savex = col;
                    savey = min(p.second, q.second);
                    return true;
                }
            }
            if (it != all.begin()) {
                --it;
                auto q = *it;
                if (intersect(p, q)) {
                    savex = col;
                    savey = min(p.second, q.second);
                    return true;
                }
            }
            all.insert(p);
        }
        for(auto p : close[col]) {
            all.erase(all.find(p));
        }
    }
    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    while (scanf("%lld", &n) == 1) {
        FOR(i,1,n) a[i].read();
        int minx = a[1].x1;
        int miny = a[1].y1;
        FOR(i,2,n) {
            minx = min(minx, a[i].x1);
            miny = min(miny, a[i].y1);
        }
        FOR(i,1,n) {
            a[i].x1 -= minx;
            a[i].x2 -= minx;
            a[i].y1 -= miny;
            a[i].y2 -= miny;
        }

        int l = 0, r = 200000, res = 0;
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
            savex += minx;
            savey += miny;
            print(savex); cout << ' ';
            print(savey); cout << ' ';
            print(res);
            cout << endl;
        }
    }
}
