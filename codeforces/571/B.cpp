
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 300111;
int n, k;
ll a[MN], sum[MN];
ll f[2][5011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

//        PR(a, n);
        FOR(i,2,n) sum[i] = a[i] - a[i-1];
        FOR(i,2,n) sum[i] = sum[i-1] + sum[i];
//        PR(sum, n);

        int each = n / k;
        int good = n % k;

        REP(t,2) FOR(i,0,good) f[t][i] = 1000111000111000LL;
        f[0][0] = 0;
        FOR(i,1,k) {
            int t = i % 2;
            FOR(j,0,good) {
                int used = i * each + j;
                f[t][j] = f[1-t][j] + sum[used] - sum[used - each + 1];

                if (j > 0) {
                    f[t][j] = min(f[t][j], f[1-t][j-1] + sum[used] - sum[used - each]);
                }
            }
        }
        cout << f[k % 2][good] << endl;
    }
}
