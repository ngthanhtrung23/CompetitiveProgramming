
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

const int MN = 2000111;

int bit[MN];

void update(int x) {
    for(int u = x; u < MN; u += u & -u)
        bit[u]++;
}

int get(int x) {
    int res = 0;
    for(int u = x; u > 0; u -= u & -u)
        res += bit[u];
    return res;
}

int n, k;

int getSegment(int u, int v) {
    return get(v-1) - get(u);
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    while (GI(n) == 1 && GI(k) == 1) {
        memset(bit, 0, sizeof bit);

        if (k+k >= n) k = n - k;

        int res = 1;
        int u = 1;
        REP(turn,n) {
            int v = u + k;

            res += 1 + getSegment(u, v);
            if (v > n) v -= n;

            update(u);
            update(u+n);
            update(v);
            update(v+n);
            u = v;

            printf("%lld ", res);
        }
        puts("");
    }
}
