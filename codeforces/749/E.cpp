
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
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 100111;
int a[MN];
int n;

int bit[MN];

#define _(X) ((X) & (-(X)))
void update(int i, int val) {
    for(; i < MN; i+=_(i))
        bit[i] += val;
}
int get(int i) {
    int res = 0;
    for(; i > 0; i -= _(i))
        res += bit[i];
    return res;
}

int f(int i, int j) {
    return i * (n - j + 1);
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(15);
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);

        long double res = 0.0;
        long double all = n * (n+1) / 2;

        // a[i] < a[j]
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            res += 0.5 * get(a[i]) / all * (n - i + 1);
            update(a[i], i);
        }

        // a[i] > a[j]
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            res -= 0.5 * get(n + 1 - a[i]) / all * (n - i + 1);
            update(n + 1 - a[i], i);
        }

        // count inversion
        memset(bit, 0, sizeof bit);
        FORD(i,n,1) {
            res += get(a[i]);
            update(a[i], 1);
        }

        cout << res << endl;
    }
}
