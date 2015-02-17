
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const long long MOD = 1e9 + 7;

int m, a[22], na;
int f[22][22][2];
long long cnt[22], gt[22];

void init() {
    na = 0;
    ++m;
    while (m) {
        a[++na] = m % 10;
        m /= 10;
    }
    reverse(a+1, a+na+1);

//    PR(a, na);
    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    FOR(i,0,na-1) FOR(cnt,0,i) FOR(lower,0,1) if (f[i][cnt][lower]) {
        FOR(cur,0,9)
            if (lower || cur <= a[i+1]) {
                int cnt2 = cnt; if (cur == 4 || cur == 7) ++cnt2;
                int lower2 = lower; if (cur < a[i+1]) lower2 = 1;
                f[i+1][cnt2][lower2] += f[i][cnt][lower];

                if (i == 0) {
                }
            }
    }

    FOR(has,0,20)
        cnt[has] = f[na][has][1];
    cnt[0]--;
}

long long g[20][20][20];

void update(long long& x, long long val) {
    x = (x + val) % MOD;
}

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x * x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long c(long long n, int k) {
    if (k < 0 || k > n) return 0;

    long long res = 1;
    FOR(x,n-k+1,n)
        res = (res * x) % MOD;
    return res * power(gt[k], MOD - 2) % MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m) {
        init();
        gt[0] = 1; FOR(i,1,20) gt[i] = gt[i-1] * i % MOD;

        long long res = 0;
//        PR0(cnt, 10);
        FOR(my,1,11) {
            memset(g, 0, sizeof g);
            g[0][0][0] = 1;
            FOR(add,0,my-1) FOR(i,0,6) FOR(sum,0,my-1) {
                FOR(mult,0,6) if (sum + add * mult < my) {
                    update(g[add+1][i + mult][sum + add * mult],
                            g[add][i][sum] * c(cnt[add], mult) % MOD * gt[mult] % MOD * c(i + mult, mult));
                }
            }

            FOR(sum,0,my-1) {
                res = (res + g[my][6][sum] * cnt[my]) % MOD;
            }
//            cout << my << ' ' << res << endl;
        }
        cout << res << endl;
    }
    return 0;
}
