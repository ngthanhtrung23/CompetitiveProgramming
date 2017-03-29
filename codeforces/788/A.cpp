
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

const int MN = 100111;
int n, tmp[MN], a[MN], s[MN];
int ln[2], nn[2];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (GI(n) == 1) {
        FOR(i,1,n) GI(tmp[i]);
        --n;
        FOR(i,1,n) a[i] = llabs(tmp[i] - tmp[i+1]);

        s[n+1] = 0;
        FORD(i,n,1) {
            s[i] = a[i] - s[i+1];
        }

        const int INF = 1e18;
        REP(t,2) ln[t] = -INF, nn[t] = INF;
        ln[(n+1) % 2] = nn[(n+1) % 2] = s[n+1];

        int res = -INF;
        FORD(i,n,1) {
            res = max(res, s[i] - nn[i % 2]);
            res = max(res, s[i] + ln[1 - i % 2]);

            ln[i % 2] = max(ln[i % 2], s[i]);
            nn[i % 2] = min(nn[i % 2], s[i]);
        }
        cout << res << endl;
    }
    return 0;
}
