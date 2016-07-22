#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int INF = 1000111000111000111LL;
 
struct Edge {
    int a, b, cap, flow, id;
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

    vector<int> trace() {
        bfs();
        vector<int> res;
        for(auto edge : e) {
            if (d[edge.a] >= 0 && d[edge.b] < 0 && edge.cap > 0) {
                res.push_back(edge.id);
            }
        }
        return res;
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

int n, m;
struct E {
    int u, v, w;
} e[30111];

vector< pair<int,int> > ke[1011];
int s, t;

bool visited[1011];
int tr[1011], tre[1011];
bool goodEdge[30111];
int first, last, qu[1011];

bool check(int eid) {
    memset(visited, 0, sizeof visited);
    visited[s] = 1;
    qu[first = last = 1] = s;

    while (first <= last) {
        int u = qu[first++];
        for(auto e : ke[u]) {
            if (e.second == eid) continue;

            int v = e.first;
            if (!visited[v]) {
                tr[v] = u;
                tre[v] = e.second;
                if (v == t) return true;

                visited[v] = 1;
                qu[++last] = v;
            }
        }
    }
    return false;
}

struct Sol {
    int cost;
    int ne;
    vector<int> res;

    Sol () {
        cost = INF;
    }
    Sol (vector<int> _e) : res(_e) {
        ne = SZ(_e);
        cost = 0;
        for(int x : _e) {
            cost += e[x].w;
        }
    }

    void print() {
        if (cost == INF) {
            cout << -1 << endl;
            return ;
        }
        cout << cost << endl;
        cout << ne << endl;
        for(auto x : res) cout << x << ' '; cout << endl;
    }
} best;

bool operator < (const Sol& a, const Sol& b) {
    return a.cost < b.cost;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(m) == 1) {
        GI(s); GI(t);
        const int BIG = 2000111000;

        FOR(i,1,n) ke[i].clear();

        FOR(i,1,m) {
            GI(e[i].u);
            GI(e[i].v);
            GI(e[i].w);

            ke[e[i].u].emplace_back(e[i].v, i);
            ke[e[i].v].emplace_back(e[i].u, i);
        }

        best.cost = INF;
        if (!check(-1)) {
            cout << 0 << endl << 0 << endl;
            continue;
        }

        memset(goodEdge, 0, sizeof goodEdge);
        int x = t;
        while (x != s) {
            int y = tr[x];
            goodEdge[tre[x]] = 1;
            x = y;
        }

        MaxFlow flow(n + 2);
        FOR(i,1,m) if (goodEdge[i] && !check(i)) {
            flow.addEdge(e[i].u, e[i].v, BIG * 5, i);
            flow.addEdge(e[i].v, e[i].u, BIG * 5, i);

            Sol cur(vector<int> {i});
            if (cur < best) best = cur;
        }
        else {
            flow.addEdge(e[i].u, e[i].v, BIG + e[i].w, i);
            flow.addEdge(e[i].v, e[i].u, BIG + e[i].w, i);
        }

        auto res = flow.getMaxFlow(s, t);
        int ne = res / BIG;
        if (ne == 2) {
            vector<int> tr = flow.trace();

            assert(SZ(tr) == 2);
            Sol cur(tr);
            if (cur < best) best = cur;
        }

        best.print();
    }
}
