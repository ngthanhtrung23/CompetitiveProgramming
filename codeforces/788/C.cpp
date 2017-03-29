
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
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

set<int> all;
int n[2], a[2][1011], f[2][1000111];

int solve() {
    n[0] = n[1] = 0;
    for(int x : all) {
        if (x == 0) return 1;

        if (x < 0) a[0][++n[0]] = -x;
        else a[1][++n[1]] = x;
    }
    REP(t,2) {
        sort(a[t]+1, a[t]+n[t]+1);
//        PR(a[t], n[t]);
    }

    if (n[0] == 0 || n[1] == 0) return -1;

    int res = 1e18;
    FOR(i,1,n[0]) FOR(j,1,n[1]) {
        int x = a[0][i], y = a[1][j];
        int g = __gcd(x, y);
        res = min(res, x / g + y / g);
    }

    memset(f, 0x3f, sizeof f);
    REP(t,2) {
        int bound = a[t][n[t]] * res;

        f[t][0] = 0;
        FOR(i,1,n[t]) {
            int x = a[t][i];
            FOR(val,x,bound) {
                if (f[t][val-x] + 1 < f[t][val])
                    f[t][val] = f[t][val-x] + 1;
            }
        }
    }

    FOR(val,1,1000110) res = min(res, f[0][val] + f[1][val]);
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int need;
    while (GI(need) == 1) {
        int k; GI(k);
        all.clear();
        FOR(i,1,k) {
            int x;
            GI(x);
            all.insert(x - need);
        }

        cout << solve() << endl;
    }
    return 0;
}
