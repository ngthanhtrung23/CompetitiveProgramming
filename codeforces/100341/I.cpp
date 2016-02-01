
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
int n;
struct Point {
    int x[4];
} a[MN];
int cx[4][MN];
int nx[4];

int getId(int t, int val) {
    return lower_bound(cx[t]+1, cx[t]+nx[t]+1, val) - cx[t];
}

void RR() {
    REP(t,4) {
        FOR(i,1,n) cx[t][i] = a[i].x[t];

        cx[t][n+1] = 0;
        sort(cx[t]+1, cx[t]+n+2);

        nx[t] = unique(cx[t]+1, cx[t]+n+2) - cx[t] - 1;

        FOR(i,1,n) {
            a[i].x[t] = getId(t, a[i].x[t]);
        }
    }
}

set<int> lx[4][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("queen2.in", "r", stdin);
    freopen("queen2.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].x[0] >> a[i].x[1];
            a[i].x[2] = a[i].x[0] + a[i].x[1];
            a[i].x[3] = a[i].x[0] - a[i].x[1];
        }
        RR();
        REP(t,4) {
            FOR(i,1,n) {
                lx[t][i].clear();
            }
            FOR(i,1,n) {
                int val = a[i].x[t];
                lx[t][val].insert(a[i].x[t ^ 1]);
            }
        }
        int res = 0;
        Point p;
        REP(t,4) p.x[t] = getId(t, 0);

        FOR(i,1,n) {
            bool can = false;
            REP(t,4) {
                int val = p.x[t];
                if (val == a[i].x[t]) {
                    int fr = min(a[i].x[t ^ 1], p.x[t ^ 1]);
                    int to = max(a[i].x[t ^ 1], p.x[t ^ 1]);

                    auto it = lx[t][val].upper_bound(fr);
                    if (it == lx[t][val].end() || *it >= to) {
                        can = true;
                        break;
                    }
                }
            }
            if (!can) break;

            REP(t,4) {
                int val = a[i].x[t];
                lx[t][val].erase(a[i].x[t ^ 1]);
            }

            p = a[i];
            res = i;
        }
        cout << res << endl;
    }
}
