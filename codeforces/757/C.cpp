
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

const ll MOD = 1e9 + 7;

const int MN = 1000111;
int gt[MN];
vector<int> h[MN];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    const int MOD = 1e9 + 7;
    gt[0] = 1;
    FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;

    int n, m;
    while (GI(n) == 1 && GI(m) == 1) {
        FOR(i,1,m) h[i].clear();
        FOR(i,1,n) {
            int k; GI(k);
            while (k--) {
                int u; GI(u);
                h[u].push_back(i);
            }
        }
        sort(h+1, h+m+1);
        int i = 1;
        int res = 1;
        
        while (i <= m) {
            int j = i;
            while (j < m && h[j+1] == h[i]) j++;

            res = res * gt[j - i + 1] % MOD;

            i = j + 1;
        }
        cout << res << endl;
    }
}
