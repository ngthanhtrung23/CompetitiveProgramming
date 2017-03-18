
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
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 200111;

pair<int,int> f[MN][5];
int n, k;
int res;
vector<int> ke[MN];

void dfs(int u, int fu) {
    // add u
    f[u][0].second++;

    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);

        // distance child -> child
        REP(mod,k) {
            REP(prev,k) {
                res += f[v][mod].second * f[u][prev].first;
                res += f[v][mod].first * f[u][prev].second;

                int add = (mod + prev + 1 + (k - 1)) / k;
                res += f[u][prev].second * f[v][mod].second * add;
            }
        }

        REP(mod,k) {
            int next = mod + 1;
            if (next == k) next = 0;

            f[u][next].first += f[v][mod].first;
            if (next == 0) f[u][next].first += f[v][mod].second;

            f[u][next].second += f[v][mod].second;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        GI(k);
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        res = 0;
        memset(f, 0, sizeof f);
        dfs(1, 0);
        cout << res << endl;
    }
    return 0;
}
