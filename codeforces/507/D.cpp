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

int n, k, m;

long long f[1011][111][2][2], p10[1011];

void update(long long& x, long long val) {
    x = (x + val) % m;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k >> m) {
        p10[0] = 1; FOR(i,1,n+1) p10[i] = (p10[i-1] * 10LL) % k;

        memset(f, 0, sizeof f);
        f[0][0][0][0] = 1;

        FOR(i,0,n-1) FOR(rem,0,k-1) FOR(good,0,1) FOR(pos,0,1)
            if (f[i][rem][good][pos])
            FOR(add,0,9) if (i < n-1 || add > 0) {
                int newGood = good;
                int newRem = (rem + add * p10[i]) % k;
                int newPos = pos; if (add) newPos = 1;
                if (newRem == 0 && newPos) newGood = 1;

                update(f[i+1][newRem][newGood][newPos], f[i][rem][good][pos]);
            }

        long long res = 0;
        FOR(rem,0,k-1)
            update(res, f[n][rem][1][1]);
        cout << res << endl;
    }
    return 0;
}
