
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

const int MN = 1011;
const int MOD = 1e9 + 7;

int n, m, k;
int cnt[MN];
int c[MN][MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    FOR(i,0,1000) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
    }

    while (GI(n) == 1) {
        GI(m); GI(k);
        memset(cnt, 0, sizeof cnt);

        FOR(i,1,n) {
            int x; GI(x);
            cnt[x]++;
        }
        sort(cnt+1, cnt+m+1);

        int all = 0, sum = 0;
        while (all < m && sum + cnt[all+1] < k) {
            ++all;
            sum += cnt[all];
        }
        if (all == m) cout << 1 << endl;
        else {
            int each = cnt[all + 1];
            int all = 0;
            FOR(i,1,n) if (cnt[i] < each) k -= cnt[i];
            FOR(i,1,n) if (cnt[i] == each) all += cnt[i];

            cout << c[all][k] << endl;
        }
    }
}
