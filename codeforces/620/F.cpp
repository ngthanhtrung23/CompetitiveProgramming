
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

int f[1000111], a[100111], res[100111], l[100111], r[100111], cur[100111], cache[100111];
int n, m;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    f[0] = 0;
    FOR(i,1,1000*1000) f[i] = f[i-1] ^ i;
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            cache[i] = f[a[i]];
        }
        FOR(i,1,m) {
            res[i] = -1;
            scanf("%d%d", &l[i], &r[i]);
        }

        FOR(i,1,n) {
            cur[i] = a[i];
            FOR(j,i+1,n) {
                int t = cache[i] ^ cache[j] ^ (a[i] < a[j] ? a[i] : a[j]);
                cur[j] = max(cur[j-1], t);
            }

            FOR(j,1,m) if (l[j] <= i && i <= r[j])
                res[j] = max(res[j], cur[r[j]]);
        }
        FOR(i,1,m) printf("%d\n", res[i]);
    }
}
