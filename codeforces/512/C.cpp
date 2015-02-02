#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

map< pair<int,int>, int > id;
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

        id[make_pair(a, b)] = e.size();

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

#define left _left
#define right _right
const int MN = 211;
int n, a[MN], left[MN], right[MN];
vector<int> ke[MN], cur;
bool visited[MN];

bool isPrime(int n) {
    for(int i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return n > 1;
}

void dfs(int u) {
    visited[u] = true;
    cur.push_back(u);

    for(auto v : ke[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        int nleft = 0, nright = 0;
        FOR(i,1,n) {
            if (a[i] % 2 == 0) left[++nleft] = i;
            else right[++nright] = i;
        }
        MaxFlow flow(nleft + nright + 2);
        int s = 0, t = nleft + nright + 1;

        FOR(i,1,nleft) flow.addEdge(s, i, 2);
        FOR(i,1,nright) flow.addEdge(nleft+i, t, 2);

        FOR(i,1,nleft) FOR(j,1,nright) {
            int u = a[ left[i] ], v = a[ right[j] ];
            if (isPrime(u + v)) {
                flow.addEdge(i, nleft + j, 1);
            }
        }

        int res = flow.getMaxFlow(s, t);
        FOR(i,1,n) ke[i].clear();
        if (res == n) {
            FOR(i,1,nleft) FOR(j,1,nright) {
                int u = a[ left[i] ], v = a[ right[j] ];
                if (isPrime(u + v)) {
                    int edge_id = id[make_pair(i, nleft + j)];
                    if (flow.e[edge_id].flow == 1) {
                        ke[ left[i] ].push_back( right[j] );
                        ke[ right[j] ].push_back( left[i] );

//                        cout << left[i] << ' ' << right[j] << endl;
                    }
                }
            }

            vector< vector< int > > path;
            memset(visited, false, sizeof visited);
            FOR(i,1,n) if (!visited[i]) {
                cur.clear();
                dfs(i);
                path.push_back(cur);
            }

            cout << path.size() << "\n";
            for(auto p : path) {
                cout << p.size();
                for(int x : p) cout << ' ' << x;
                cout << "\n";
            }
        }
        else cout << "Impossible" << endl;
    }
    return 0;
}
