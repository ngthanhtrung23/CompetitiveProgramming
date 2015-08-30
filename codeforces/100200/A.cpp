#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), g(n), q(n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            REP(i,n) ptr[i] = 0;
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

private:
    bool bfs() {
        int qh = 0, qt = 0;
        q[qt++] = s;
        REP(i,n) d[i] = -1;
        d[s] = 0;

        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            REP(i,g[v].size()) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

bool visited[1011];
int n;
vector< pair<int,int> > get(const MaxFlow& flow, int s, int t) {
    vector< pair<int,int> > res;

    queue<int> qu;
    memset(visited, 0, sizeof visited);
    visited[s] = true;
    qu.push(s);

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for(int edge_id : flow.g[u]) {
            auto e = flow.e[edge_id];
            if (e.cap == e.flow) continue;

            int v = e.b;
            if (!visited[v]) {
                visited[v] = true;
                qu.push(v);
            }
        }
    }
//    PR(visited, n);

    FOR(i,1,n) if (visited[i]) {
        for(int edge_id : flow.g[i]) {
            auto e = flow.e[edge_id];
            int j = e.b;

            if (!visited[j]) {
                res.push_back(make_pair(i, j));
            }
        }
    }

    REP(i,res.size()) {
        if (res[i].first > res[i].second) {
            swap(res[i].first, res[i].second);
        }
    }
    sort(res.begin(), res.end());
//    cout << "cut:" << endl;
//    for(auto e : res) cout << e.first << ' ' << e.second << "    ";
//    cout << endl;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);
    int m, s, t;
    while (cin >> n >> m >> s >> t) {
        MaxFlow flow1(n+1), flow2(n+1);
        FOR(i,1,m) {
            int u, v, cap; cin >> u >> v >> cap;
            if (cap == 0) continue;
            flow1.addEdge(u, v, cap);
            flow1.addEdge(v, u, cap);

            flow2.addEdge(u, v, cap);
            flow2.addEdge(v, u, cap);
        }
        int x = flow1.getMaxFlow(s, t), y = flow2.getMaxFlow(t, s);
        auto t1 = get(flow1, s, t);
        auto t2 = get(flow2, t, s);
        if (t1 == t2) cout << "UNIQUE" << endl;
        else cout << "AMBIGUOUS" << endl;
    }
}