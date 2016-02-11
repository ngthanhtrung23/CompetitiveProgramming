
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

vector< vector<int> > res;
const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
    int id;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), q(n), g(n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap, int id) {
        Edge e1 = { a, b, cap, 0, id };
        Edge e2 = { b, a, 0, 0, id };
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

    void go(int u, vector<int>& p) {
        for(int eid : g[u]) {
            if (e[eid].flow == 1) {
                e[eid].flow = 0;
                if (e[eid].id > 0) {
                    p.push_back(e[eid].id);
                }

                go(e[eid].b, p);
            }
        }
    }

    void trace(int s, int t) {
        for(int eid: g[s]) {
            if (e[eid].flow == 1) {
                e[eid].flow = 0;
                vector<int> p;
                if (e[eid].id > 0) p.push_back(e[eid].id);

                go(e[eid].b, p);
                res.push_back(p);
            }
        }
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

const int MN = 5011;
int c[MN], nc;
pair<int,int> a[MN];
int n, w;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("wall.in", "r", stdin);
    freopen("wall.out", "w", stdout);
    while (cin >> n >> w) {
        c[++nc] = 0;
        c[++nc] = w;
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
            c[++nc] = a[i].first;
            c[++nc] = a[i].second;
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) {
            a[i].first = lower_bound(c+1, c+nc+1, a[i].first) - c;
            a[i].second = lower_bound(c+1, c+nc+1, a[i].second) - c;
        }
        MaxFlow flow(2*nc);
        FOR(i,1,nc) {
            int u = 2*i - 2;
            int v = 2*i - 1;
            if (i == 1 || i == nc) flow.addEdge(u, v, n, -1);
            else flow.addEdge(u, v, 1, -1);
        }
        FOR(i,1,n) {
            int u = 2*a[i].first - 1;
            int v = 2*a[i].second - 2;
            flow.addEdge(u, v, 1, i);
        }
        int t = flow.getMaxFlow(0, 2*nc-1);
        cout << t << endl;
        res.clear();
        flow.trace(1, 2*nc-2);
        for(auto p : res) {
            for(int x : p) cout << x << ' ';
            cout << '\n';
        }
    }
}
