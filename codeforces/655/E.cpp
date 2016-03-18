
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
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2000111;
const int MOD = 1e9 + 7;
int last[33];
int a[MN], f[MN];
string s;
int n, k, m;
char tmp[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld%lld\n", &n, &k) == 2) {
        scanf("%s\n", &tmp[0]);
        s = string(tmp);
        m = SZ(s);
        s = " " + s + " ";

        FOR(i,1,m) a[i] = s[i] - 'a';
//        PR(a, m);

        memset(last, 0, sizeof last);
        f[0] = 1;
        FOR(i,1,m) {
            f[i] = f[i-1] * 2 % MOD;
            if (last[a[i]] > 0) {
                f[i] = (f[i] - f[last[a[i]] - 1] + MOD) % MOD;
            }

            last[a[i]] = i;
        }

        FOR(i,m+1,m+n) {
            int best = 0;
            REP(add,k) {
                if (last[add] < last[best]) best = add;
            }
            a[i] = best;

            f[i] = f[i-1] * 2 % MOD;
            if (last[a[i]] > 0) {
                f[i] = (f[i] - f[last[a[i]] - 1] + MOD) % MOD;
            }
            last[a[i]] = i;
        }
        cout << f[m+n] << endl;
    }
}
