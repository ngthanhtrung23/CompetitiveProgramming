
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
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 100111;
int t[MN], f[MN];
int n;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) GI(t[i]);
        t[0] = -1000111;
        FOR(i,1,n) {
            // single
            f[i] = f[i-1] + 20;

            int j = lower_bound(t, t+i, t[i] - 89) - t;
            f[i] = min(f[i], f[j-1] + 50);

            j = lower_bound(t, t+i, t[i] - 1440 + 1) - t;
            f[i] = min(f[i], f[j-1] + 120);
        }
        FOR(i,1,n) printf("%lld\n", f[i] - f[i-1]);
    }
}
