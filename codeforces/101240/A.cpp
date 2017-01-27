
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

int m, n, k;
const int INF = 1e15;

int solve1() {
    if (k >= m || k >= n) return INF;
    if (m > n) swap(m, n);

    if (n >= 2*k + 3) {
        return (m + k - 1) / k;
    }
    return INF;
}
int solve2() {
    if (k >= m || k >= n) return INF;
    if (m > n) swap(m, n);

    if (m >= 2*k+1 && n >= 2*k+3) {
        if (k == 1) return 5;
        else return 4;
    }
    return INF;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> m >> n >> k;
        int res = min(solve1(), solve2());
        if (res == INF) res = -1;
        cout << "Case #" << test << ": " << res << '\n';
    }
}
