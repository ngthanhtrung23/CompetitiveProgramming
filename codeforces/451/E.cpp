#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n;
long long s, f[22];
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
const long long MOD = 1000000007;

long long powMod(long long x, long long k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = powMod(x, k >> 1);
    mid = mid * mid % MOD;
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long cache[1011];
inline long long inverse(long long x) {
    if (cache[x]) return cache[x];
    return cache[x] = powMod(x, MOD - 2);
}

long long get(long long s, int n) {
    if (s < 0) return 0;
    if (s == 0) return 1;

    long long res = 1;
    for(long long i = s+1; i < s+n; ++i)
        res = res * (i % MOD) % MOD;
    for(long long i = 2; i < n; ++i)
        res = res * inverse(i) % MOD;
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> s) {
        REP(i,n) cin >> f[i];

        long long res = 0;
        REP(mask,TWO(n)) {
            long long ss = s;
            REP(i,n) if (CONTAIN(mask,i)) ss -= f[i] + 1;

            if (__builtin_popcount(mask) & 1) res = (res - get(ss, n) + MOD) % MOD;
            else res = (res + get(ss, n)) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}

