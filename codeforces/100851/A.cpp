
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("adjustment.in", "r", stdin);
    freopen("adjustment.out", "w", stdout);
    ll n;
    int q;
    while (scanf("%lld%d\n", &n, &q) == 2) {
        ll sumRow = 0;
        ll sumCol = 0;
        set<int> rows, cols;

        while (q--) {
            char typ;
            ll u;
            scanf("%c %lld\n", &typ, &u);
            if (typ == 'R') {
                if (rows.count(u)) { // this row is already removed
                    puts("0");
                    continue;
                }
                rows.insert(u);
                ll res = u * n +  n*(n+1) / 2LL;
                res -= SZ(cols) * u;
                res -= sumCol;
                printf("%lld\n", res);

                sumRow += u;
            }
            else {
                if (cols.count(u)) {
                    puts("0");
                    continue;
                }
                cols.insert(u);
                ll res = u * n +  n*(n+1) / 2LL;
                res -= SZ(rows) * u;
                res -= sumRow;
                printf("%lld\n", res);

                sumCol += u;
            }
        }
    }
}
