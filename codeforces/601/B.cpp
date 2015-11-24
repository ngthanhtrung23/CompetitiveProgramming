
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

int n, a[MN], l[MN], r[MN], st[MN], top;
ll x[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int q;
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            int sx = 0;
            FOR(i,u,v-1)
                x[++sx] = abs(a[i+1] - a[i]);

            st[0] = 0;
            top = 0;
            FOR(i,1,sx) {
                while (top && x[st[top]] <= x[i]) --top;
                l[i] = st[top] + 1;
                st[++top] = i;
            }
            st[0] = sx+1;
            top = 0;
            FORD(i,sx,1) {
                while (top && x[st[top]] < x[i]) --top;
                r[i] = st[top] - 1;
                st[++top] = i;
            }

            ll res = 0;
            FOR(i,1,sx) {
                res += x[i] * (i - l[i] + 1LL) * (r[i] - i + 1LL);
            }
            printf("%lld\n", res);
        }
    }
}
