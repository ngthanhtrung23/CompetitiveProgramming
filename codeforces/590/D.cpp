
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 155;
int f[2][MN][6011];
int a[MN], n, k, s;
const int oo = 1000111000;

void initF(int t) {
    memset(f[t], 0x3f, sizeof f[t]);
}

void update(int& x, int val) {
    x = min(x, val);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> s) {
        if (s > 6000) s = 6000;
        FOR(i,1,n) cin >> a[i];

        initF(0);
        f[0][0][0] = 0;

        FOR(i,0,n-1) {
            int i2 = i % 2;
            initF(1 - i2);
            FOR(good,0,i) FOR(nSwap,0,s)
                if (f[i2][good][nSwap] < oo) {
                    update(f[1-i2][good][nSwap], f[i2][good][nSwap]);
                    if (good < k && nSwap + i - good <= s) {
                        update(f[1-i2][good+1][nSwap + i - good],
                                f[i2][good][nSwap] + a[i+1]);
                    }
                }
        }
        int res = oo;
        FOR(nSwap,0,s)
            res = min(res, f[n % 2][k][nSwap]);
        cout << res << endl;
    }
}
