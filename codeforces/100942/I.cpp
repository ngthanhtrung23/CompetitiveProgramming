
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

struct Point {
    int x[4];
};
bool operator < (const Point& a, const Point& b) {
    REP(i,4)
        if (a.x[i] != b.x[i]) return a.x[i] < b.x[i];
    return false;
}
bool operator == (const Point& a, const Point& b) {
    REP(i,4)
        if (a.x[i] != b.x[i]) return false;
    return true;
}

multiset< pair<int,Point> > f[16];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int q;
    while (scanf("%lld", &q) == 1) {
        REP(i,16) f[i].clear();

        while (q--) {
            int typ; scanf("%lld", &typ);
            Point cur;
            REP(i,4) scanf("%lld", &cur.x[i]);

            int res = -1;
            REP(mask,16) {
                if (typ == 1 || typ == 2) {
                    int val = 0;
                    REP(i,4) if ((mask >> i) & 1) {
                        val += cur.x[i];
                    }
                    else {
                        val -= cur.x[i];
                    }

                    if (typ == 1) {
                        f[mask].insert(make_pair(val, cur));
                    }
                    else if (typ == 2) {
                        f[mask].erase(f[mask].find(make_pair(val, cur)));
                    }
                }
                else {
                    int t = 0;
                    REP(i,4) {
                        t += llabs(cur.x[i] - f[mask].begin()->second.x[i]);
                    }
                    res = max(res, t);
                }
            }
            if (typ == 3) printf("%lld\n", res);
        }
    }
}
