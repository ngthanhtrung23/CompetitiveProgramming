#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int V;
vector<int> G[2011];

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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> V) {
        REP(i,V) G[i].clear();
        REP(i,V) {
            REP(j,V) {
                int u; cin >> u;
                if (u) G[i].push_back(j);
            }
        }
        DirectedDfs tree;
        if (tree.scc.size() == 1) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
    return 0;
}
