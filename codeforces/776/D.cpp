
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
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 200111;

int nRoom, nSwitch, status[MN];
vector<int> switches[MN];

vector<int> g[MN], gt[MN];
vector<bool> used;
vector<int> order, comp;
void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs1(to);
	}
	order.push_back (v);
}
void dfs2 (int v, int cl) {
    comp[v] = cl;
    for (size_t i=0; i<gt[v].size(); ++i) {
        int to = gt[v][i];
        if (comp[to] == -1)
            dfs2 (to, cl);
	}
}

void addEdge(int u, int v) {
    g[u].push_back(v);
    gt[v].push_back(u);
}

int get(int u, int val) {
    return u*2 + val;
}

int32_t main() {
    while (GI(nRoom) == 1 && GI(nSwitch) == 1) {
        FOR(i,1,nRoom) switches[i].clear();
        FOR(i,1,nRoom) GI(status[i]);

        FOR(i,1,nSwitch) {
            int t; GI(t);
            REP(index,t) {
                int room; GI(room);
                switches[room].push_back(i);
            }
        }

        FOR(i,0,MN-1) {
            g[i].clear();
            gt[i].clear();
        }
        used.clear();
        order.clear();
        comp.clear();

        int n = 2 * nSwitch;

        // init graph
        FOR(i,1,nRoom) {
            assert(SZ(switches[i]) == 2);
            int u = switches[i][0] - 1;
            int v = switches[i][1] - 1;

            if (status[i] == 0) {
                addEdge(get(u, 0), get(v, 1));
                addEdge(get(u, 1), get(v, 0));

                addEdge(get(v, 0), get(u, 1));
                addEdge(get(v, 1), get(u, 0));
            }
            else {
                addEdge(get(u, 0), get(v, 0));
                addEdge(get(u, 1), get(v, 1));

                addEdge(get(v, 0), get(u, 0));
                addEdge(get(v, 1), get(u, 1));
            }
        }

        used.assign(n, false);
        REP(i,n)
            if (!used[i]) dfs1(i);

        comp.assign (n, -1);
        for (int i=0, j=0; i<n; ++i) {
            int v = order[n-i-1];
            if (comp[v] == -1) dfs2 (v, j++);
        }

        bool ok = true;
        REP(i,n)
            if (comp[i] == comp[i^1]) {
                ok = false;
                break;
            }

        cout << (ok ? "YES" : "NO") << endl;
    }
}
