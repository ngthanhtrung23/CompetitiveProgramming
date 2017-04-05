
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

struct Cup {
    int c, w;
    int sumc, sumw;
} a[2][MN];

bool operator < (const Cup& a, const Cup& b) {
    if (a.c != b.c) return a.c < b.c;
    return a.w > b.w;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n[2], d;
    while (GI(n[0]) == 1) {
        GI(n[1]); GI(d);

        REP(t,2) {
            FOR(i,1,n[t]) {
                GI(a[t][i].c);
                GI(a[t][i].w);
            }
            sort(a[t]+1, a[t]+n[t]+1);

            FOR(i,1,n[t]) {
                a[t][i].sumc = a[t][i-1].sumc + a[t][i].c;
                a[t][i].sumw = a[t][i-1].sumw + a[t][i].w;
            }
        }

        int answer = 0;
        FOR(i,1,n[0]) {
            int l = 1, r = n[1], res = n[1] + 1;
            while (l <= r) {
                int mid = (l + r) >> 1;

                if (a[0][n[0]].sumw - a[0][i-1].sumw
                        + a[1][n[1]].sumw - a[1][mid-1].sumw <= d) {
                    res = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }

            if (res <= n[1]) {
                answer = max(answer,
                        a[0][n[0]].sumc - a[0][i-1].sumc
                        + a[1][n[1]].sumc - a[1][res-1].sumc);
            }
        }
        cout << answer << endl;
    }
    return 0;
}
