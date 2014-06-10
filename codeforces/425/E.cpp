#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 511;
const int MOD = 1000000007;

int lt[1000111], f[2][MN][MN];

void update(int &x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

inline int mult(int a, int b) {
    return a * (long long) b % MOD;
}

inline int mult(int a, int b, int c) {
    return mult(mult(a, b), c);
}

inline int sub(int a, int b) {
    return (a >= b) ? (a - b) : (a + MOD - b);
}

int n, k;

int main() {
    ios :: sync_with_stdio(false);
    lt[0] = 1;
    FOR(i,1,1000000) lt[i] = (lt[i-1] * 2) % MOD;

    while (cin >> n >> k) {
        memset(f, 0, sizeof f);
        if (k == 0) {
            cout << 1 << endl;
            continue;
        }
        FOR(i,1,n) {
            int turn = i % 2;
            f[turn][0][0] = 1;

            memset(f[1-turn], 0, sizeof f[1-turn]);

            FOR(cnt,0,k) FOR(last,0,i)
            if (f[turn][cnt][last]) {
                update(f[1-turn][cnt][last], mult(lt[last], f[turn][cnt][last]));
                if (last < i) update(f[turn][cnt+1][i], 
                    mult(sub(lt[i-last], 1), f[turn][cnt][last]));
            }
        }
        int res = 0;
        FOR(last,1,n)
            update(res, f[n%2][k][last]);
        cout << res << endl;
    }

    return 0;
}
