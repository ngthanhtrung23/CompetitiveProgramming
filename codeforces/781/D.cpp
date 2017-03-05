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

#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
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
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%d", &x); }

const int MN = 505;
bitset<MN> can[2][62][MN], rot[2][62][MN];
int n, m;

ll solve() {
    FOR(u,1,n) FOR(v,1,n)
        if (can[0][60][u][v]) return -1;

    ll res = 0;
    set<int> start;
    int need = 0;

    FORD(p2,59,0) {
        set<int> newStart;
        FOR(u,1,n) FOR(v,1,n) if (can[need][p2][u][v]) {
            if (start.empty() || start.count(u)) {
                newStart.insert(v);
            }
        }

        if (!newStart.empty()) {
            start = newStart;
            need ^= 1;
            res += 1LL<< p2;
        }
    }
    const ll INF = 1e18;
    if (res > INF) return -1;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        memset(can, 0, sizeof can);
        FOR(i,1,m) {
            int u, v, typ;
            cin >> u >> v >> typ;
            can[typ][0][u][v] = true;
        }

        FOR(p2,0,59) {
            REP(typ,2) FOR(u,1,n) FOR(v,1,n)
                rot[typ][p2][v][u] = can[typ][p2][u][v];

            FOR(u,1,n) FOR(v,1,n) {
                can[0][p2+1][u][v] = (can[0][p2][u] & rot[1][p2][v]).count() > 0;
                can[1][p2+1][u][v] = (can[1][p2][u] & rot[0][p2][v]).count() > 0;
            }
        }

        cout << solve() << endl;
    }
    return 0;
}
