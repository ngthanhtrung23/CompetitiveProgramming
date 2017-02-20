
#include <sstream>
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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 100111;
const int MOD = 1e9 + 7;
int gt[MN], inv_gt[MN];

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
    if (k < 0 || k > n) return 0;
    if (n < 0) return 0;

    return gt[n] * inv_gt[k] % MOD * inv_gt[n-k] % MOD;
}

int seq(int n, int k) {
    if (n == 0) {
        if (k == 0) return 1;
        return 0;
    }
    if (k == 0) return 0;
    if (k > n) return 0;

    return C(n-1, k-1);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    gt[0] = 1;
    FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;
    FOR(i,0,MN-1) inv_gt[i] = inverse(gt[i]);

    int sa, sb, h;
    while (cin >> sa >> sb >> h) {
        int good = 0, all = 0;

        FOR(na,0,sa) {
            FOR(nb,na-1,na+1) {
                if (nb < 0 || nb > sb) continue;

                int cur = seq(sa, na) * seq(sb, nb) % MOD;
                if (na == nb) all = (all + 2*cur) % MOD;
                else all = (all + cur) % MOD;

                cur = 0;
                if ((h+1) * nb <= sb) {
                    cur = seq(sa, na) * seq(sb - h * nb, nb) % MOD;
                }
                if (na == nb) good = (good + 2*cur) % MOD;
                else good = (good + cur) % MOD;
            }
        }

        cout << good * inverse(all) % MOD << endl;
    }

    return 0;
}
