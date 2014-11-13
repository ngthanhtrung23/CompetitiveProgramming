#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int V;
vector<int> G[MN];

struct DirectedDfs {
    vector<int> num, low, current, S;
    int counter;
    vector< vector<int> > scc;

    DirectedDfs() : num(V, -1), low(V, 0), current(V, 0), counter(0) {
        REP(i,V) if (num[i] == -1) dfs(i);
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        REP(j, G[u].size()) {
            int v = G[u][j];
            if (num[v] == -1) dfs(v);
            if (current[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            scc.push_back(vector<int>());
            while (1) {
                int v = S.back(); S.pop_back(); current[v] = 0;
                scc.back().push_back(v);
                if (u == v) break;
            }
        }
    }
};

int to[MN], sccId[MN], out[MN], in[MN];
set< pair<int,int> > edges;
vector<int> noIn, noOut;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> V) {
        REP(i,V) G[i].clear();
        REP(i,V) {
            int u; cin >> u;
            --u;
            to[i] = u;
            G[i].push_back(u);
        }

        // Initialize SCC
        DirectedDfs tree;
        // REP(i,tree.scc.size()) {
            // PR0(tree.scc[i], tree.scc[i].size());
        // }

        // If there's only one SCC
        if (tree.scc.size() == 1) {
            cout << 0 << endl;
            continue;
        }

        // Find sccId
        REP(i,tree.scc.size()) {
            for(int u : tree.scc[i])
                sccId[u] = i;
        }

        // Create edges between SCC
        edges.clear();
        memset(out, 0, sizeof out);
        memset(in, 0, sizeof in);
        REP(i,V) {
            int u = sccId[i];
            int v = sccId[to[i]];
            if (u == v) continue;
            if (!edges.count(make_pair(u, v))) {
                edges.insert(make_pair(u, v));
                out[u]++;
                in[v]++;
            }
        }

        // Find 0-in and 0-out SCC
        noIn.clear(); noOut.clear();
        REP(i,tree.scc.size()) {
            if (out[i] == 0) {
                noOut.push_back(i);
            }
            if (in[i] == 0) {
                noIn.push_back(i);
            }
        }
        // PR0(noIn, noIn.size());
        // PR0(noOut, noOut.size());
        vector< pair<int,int> > res;
        REP(i,max(noIn.size(), noOut.size())) {
            int s1 = noIn[i % noIn.size()];
            int s2 = noOut[(i+1) % noOut.size()];

            int u = tree.scc[s1][0];
            int v = tree.scc[s2][0];

            res.push_back(make_pair(v + 1, u + 1));
        }
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i].first << ' ' << res[i].second << endl;
    }
    return 0;
}

