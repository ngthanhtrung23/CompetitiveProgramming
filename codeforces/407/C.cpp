#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const long long MOD = 1000000007;
const int MN = 100111;
long long a[MN], add[111][MN];
long long c[MN][111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);

    FOR(i,0,100000) {
        c[i][0] = 1;
        FOR(j,1,min(100,i))
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
    }

    int n, q;
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> a[i];
        memset(add, 0, sizeof add);
        FOR(i,1,q) {
            int l, r, k; cin >> l >> r >> k;
            add[k][l] = (add[k][l] + 1) % MOD;
            FOR(x,0,k) {
                add[x][r+1] = (add[x][r+1] + MOD - c[r-l+k-x][k-x])% MOD;
            }
        }
        FORD(k,100,0) {
            FOR(i,1,n) add[k][i] = (add[k][i] + add[k][i-1]) % MOD;
            if (k) {
                FOR(i,1,n) add[k-1][i] = (add[k][i] + add[k-1][i]) % MOD;
            }
        }
        FOR(i,1,n) {
            cout << (a[i] + add[0][i]) % MOD << ' ';
        }
        cout << endl;
    }
    return 0;
}
