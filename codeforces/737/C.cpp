
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

const int MN = 200111;

int n, root;
int a[MN];
int cnt[MN], sum[MN];
int equal0[MN];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(root) == 1) {
        FOR(i,1,n) GI(a[i]);
        int res = 0;
        if (a[root]) {
            a[root] = 0;
            ++res;
        }

        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) if (i != root) ++cnt[a[i]];

        memset(equal0, 0, sizeof equal0);
        FOR(i,0,n) {
            if (cnt[i] == 0) equal0[i] = 1;
            if (i) equal0[i] += equal0[i-1];
        }
        FOR(i,0,n) {
            sum[i] = cnt[i];
            if (i) sum[i] += sum[i-1];
        }

        if (n > 1) {
            int change = 1000111000;
            FOR(k,1,n-1) {
                int outside = n - 1 - (sum[k] - sum[0]);
                int missing = equal0[k] - equal0[0];

                int cur = max(outside, missing);
                change = min(change, cur);
            }
            res += change;
        }

        cout << res << endl;
    }
}
