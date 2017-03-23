
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

const int MN = 1000111;

int n;
vector< pair<int,int> > ke[MN];

void addEdge(int u, int v, int cost) {
    ke[u].emplace_back(v, cost);
}

int id[2][MN], nid;
int f[MN];

void build(int t, int i, int l, int r) {
    if (l == r) {
        id[t][i] = ++nid;
        if (t == 0) {
            addEdge(id[t][i], l, 0);
        } else {
            addEdge(l, id[t][i], 0);
        }
        return ;
    }
    int mid = (l + r) >> 1;

    build(t, i<<1, l, mid);
    build(t, i<<1|1, mid+1, r);

    id[t][i] = ++nid;

    if (t == 0) {
        addEdge(id[t][i], id[t][i<<1], 0);
        addEdge(id[t][i], id[t][i<<1|1], 0);
    } else {
        addEdge(id[t][i<<1], id[t][i], 0);
        addEdge(id[t][i<<1|1], id[t][i], 0);
    }
}

void update(int t, int i, int l, int r, int u, int v, int x, int cost) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        if (t == 0) {
            addEdge(x, id[t][i], cost);
        }
        else {
            addEdge(id[t][i], x, cost);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    update(t, i<<1, l, mid, u, v, x, cost);
    update(t, i<<1|1, mid+1, r, u, v, x, cost);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (GI(n) == 1) {
        int m; GI(m);
        int start; GI(start);

        nid = n;
        REP(t,2) build(t, 1, 1, n);

        while (m--) {
            int typ; GI(typ);
            if (typ == 1) {
                int from, to, cost;
                GI(from); GI(to); GI(cost);

                update(0, 1, 1, n, to, to, from, cost);
            }
            else if (typ == 2) {
                int l, r, from, cost;
                GI(from); GI(l); GI(r); GI(cost);
                update(0, 1, 1, n, l, r, from, cost);
            }
            else {
                int l, r, to, cost;
                GI(to); GI(l); GI(r); GI(cost);
                update(1, 1, 1, n, l, r, to, cost);
            }
        }

        memset(f, 0x3f, sizeof f);
        int INF = f[0];
        set< pair<int,int> > all;
        all.insert(make_pair(0, start));
        f[start] = 0;

        while (!all.empty()) {
            int u = all.begin()->second;
            int l = all.begin()->first;
            all.erase(all.begin());
            if (l != f[u]) continue;

            for (auto e : ke[u]) {
                int v = e.first, cost = e.second;

                if (f[v] > f[u] + cost) {
                    f[v] = f[u] + cost;
                    all.insert(make_pair(f[v], v));
                }
            }
        }

        FOR(i,1,n) {
            if (f[i] == INF) f[i] = -1;
            printf("%lld ", f[i]);
        }
        puts("");

        FOR(i,1,nid) ke[i].clear();
    }
    return 0;
}
