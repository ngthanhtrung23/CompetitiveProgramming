
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

const int MN = 1000111;
int lab[MN];
struct DSU {
    void init(int n) {
        REP(i,n+2) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int n, m;
int deg[MN], hasSelf[MN];
DSU dsu;
int any, self;

int solve() {
    FOR(i,1,n) if (dsu.getRoot(i) != dsu.getRoot(any)) {
        if (hasSelf[i] || deg[i])
            return 0;
    }

    int res = 0;
    FOR(i,1,n) {
        res += deg[i] * (deg[i] - 1) / 2;
    }

    res = res + self * (self - 1) / 2;
    res = res + self * (m - self);
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (GI(n) == 1) {
        GI(m);
        memset(deg, 0, sizeof deg);
        memset(hasSelf, 0, sizeof hasSelf);
        dsu.init(n);

        any = 0;
        self = 0;
        REP(eid,m) {
            int u, v; GI(u); GI(v);
            any = u;
            if (u == v) {
                ++self;
                hasSelf[u] = 1;
            } else {
                dsu.merge(u, v);
                ++deg[u];
                ++deg[v];
            }
        }

        // 2 normal edges.
        int res = solve();

        cout << res << endl;
    }
    return 0;
}
