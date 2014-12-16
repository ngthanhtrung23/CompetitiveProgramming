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

long long f[15][111][2];
int x[15];
int cache[111];

bool isPrime(int n) {
    if (cache[n] >= 0) return cache[n];
    for(int i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return n > 1;
}

bool areCoprime(int a, int b) {
    if (a == 0) return b == 1;
    if (b == 0) return a == 1;
    return __gcd(a, b) == 1;
}

long long get(long long bound) {
    if (bound < 10) return 0;

    int cur = 0;
    while (bound) {
        x[++cur] = bound % 10;
        bound /= 10;
    }
    reverse(x+1, x+cur+1);

    // Same number of digits
    memset(f, 0, sizeof f);
    FOR(i,10,x[1]*10+x[2])
        if (!isPrime(i))
            f[2][i][ i < x[1]*10 + x[2] ] = 1;

    FOR(has,2,cur-1)
        FOR(last,0,99)
           FOR(lower,0,1)
            if (f[has][last][lower]) {
                FOR(add,0,9) if (lower || add <= x[has+1]) {
                    int next = (last % 10) * 10 + add;
                    if (!isPrime(next) && areCoprime(next, last)) {
                        int newLower = lower;
                        if (add < x[has+1]) newLower = 1;
                        f[has+1][next][newLower] += f[has][last][lower];
                    }
                }
            }

    long long res = 0;
    FOR(last,0,99)
        FOR(lower,0,1)
            res += f[cur][last][lower];

    // less digits
    memset(f, 0, sizeof f);
    FOR(i,10,99)
        if (!isPrime(i))
            f[2][i][1] = 1;

    FOR(has,2,cur-1)
        FOR(last,0,99)
           FOR(lower,0,1)
            if (f[has][last][lower]) {
                FOR(add,0,9) if (lower || add <= x[has+1]) {
                    int next = (last % 10) * 10 + add;
                    if (!isPrime(next) && areCoprime(next, last)) {
                        int newLower = lower;
                        if (add < x[has+1]) newLower = 1;
                        f[has+1][next][newLower] += f[has][last][lower];
                    }
                }
            }
    FOR(len,2,cur-1)
        FOR(last,0,99)
            FOR(lower,0,1)
                res += f[len][last][lower];

    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    memset(cache, -1, sizeof cache);
    FOR(test,1,ntest) {
        long long a, b; cin >> a >> b;
        cout << "Case #" << test << ": " << get(b) - get(a-1) << endl;
    }
    return 0;
}
