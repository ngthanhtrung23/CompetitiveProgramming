#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << ' '; cout << endl; }
#define PR0(A, n) { cout << #A << " = "; REP(_, n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

int f[22][TWO(10) + 11][2][2];
int sum[TWO(10) + 11];
int digits[22], nDigits;

void expand(int bound) {
    stringstream ss; ss << bound;
    string s = ss.str();

    nDigits = SZ(s);
    FORD(i,nDigits,1) {
        digits[i] = s[i-1] - '0';
    }
}

void cal(int bound, int sign) {
    expand(bound);

    memset(f, 0, sizeof f);
    f[0][0][0][0] = 1;

    FOR(len,0,nDigits-1) REP(mask,TWO(10)) REP(lower,2) REP(positive,2) {
        int cur = f[len][mask][lower][positive];
        if (!cur) continue;

        REP(add,10) if (lower || add <= digits[len+1]) {
            int lower2 = lower;
            if (!lower && add < digits[len+1]) lower2 = 1;

            int positive2 = positive;
            if (add > 0) positive2 = 1;

            int mask2 = mask;
            if (positive2) mask2 |= TWO(add);

            f[len+1][mask2][lower2][positive2] += cur;
        }
    }

    REP(mask,TWO(10)) if (f[nDigits][mask][1][1]) {
        sum[mask] += sign * f[nDigits][mask][1][1];
    }
}

void magic() {
    int K = 10;
    for(int b=0; b<K; b++) {
        int f=0, t=(1<<b);
        for(int g=0; g<(1<<(K-1-b)); f+=(1<<(b+1)), t+=(1<<(b+1)), g++)
            for(int i=0; i<(1<<b); i++)
                sum[f|i] += sum[t|i];
    }
}

const int MOD = 1e9 + 7;

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    int mid = power(x, k >> 1);
    mid = mid * mid % MOD;

    if (k & 1) return mid * x % MOD;
    return mid;
}

int inverse(int x) {
    return power(x, MOD - 2);
}

int C(int n, int k) {
    if (n < 0) return 0;
    if (k < 0 || k > n) return 0;

    assert(n >= k);

    int res = 1;
    for (int i = n - k + 1; i <= n; i++) {
        res = (res * (i % MOD)) % MOD;
    }

    for (int i = 1; i <= k; i++)
        res = res * inverse(i) % MOD;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int ntest; cin >> ntest;
    while (ntest--) {
        int a, b, k, d;
        cin >> a >> b >> k >> d;

        memset(sum, 0, sizeof sum);

        // Calculate sum[i] = count(numbers with digit bitmask i)
        cal(b+1, +1);
        cal(a, -1);

        // Update sum[i] = count(numbers containing all digits in bitmask i)
        magic();

        // Calculate result.
        int res = 0;
        REP(mask,TWO(10)) {
            int nBit = __builtin_popcount(mask);
            if (nBit < d) continue;

            int cur = C(sum[mask], k) * C(nBit, d) % MOD;

            if ((nBit - d) % 2 == 0) res = (res + cur) % MOD;
            else res = (res - cur + MOD) % MOD;
        }
        cout << res << '\n';
    }
    return 0;
}
