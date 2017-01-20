
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

const int MN = 333;

int n, m;
int a[MN][MN], f[MN][MN];

void update(int& f, int c) {
    f = min(f, c);
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    FOR(test,1,ntest) {
        GI(n); GI(m);
        FOR(i,1,n) {
            FOR(j,1,m) GI(a[i][j]);
            sort(a[i]+1, a[i]+m+1);

            FOR(j,1,m) a[i][j] += a[i][j-1];
            FOR(j,1,m) a[i][j] += j*j;
        }

        const int MAX = 1000111000111000111LL;
        FOR(i,0,n) FOR(j,0,n) f[i][j] = MAX;

        f[0][0] = 0;
        FOR(i,0,n-1) FOR(j,i,n) {
            int cur = f[i][j];
            if (cur == MAX) continue;

            FOR(x,0,m) {
                int j2 = j + x;
                if (j2 < i+1) continue;
                if (j2 > n) j2 = n;

                update(f[i+1][j2], cur + a[i+1][x]);
            }
        }
        cout << "Case #" << test << ": " << f[n][n] << endl;
    }
}
