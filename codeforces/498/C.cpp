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

int eu[111], ev[111], id[111], cnt[111];
int a[111], n, m;
int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,m) cin >> eu[i] >> ev[i];
        int res = 0;
        vector<int> primes;
        FOR(i,1,n) {
            int u = a[i];
            for(int p = 2; p*p <= u; ++p) {
                if (u % p == 0) {
                    primes.push_back(p);
                    while (u % p == 0) u /= p;
                }
            }
            if (u > 1) primes.push_back(u);
        }
        sort(primes.begin(), primes.end());
        primes.resize(unique(primes.begin(), primes.end()) - primes.begin());
        for(int p : primes) {
            int nleft = 0, nright = 0;
            FOR(i,1,n)
            if (a[i] % p == 0) {
                if (i % 2 == 1) id[i] = ++nleft; else id[i] = ++nright;
                cnt[i] = 0;
                while (a[i] % p == 0) {
                    ++cnt[i];
                    a[i] /= p;
                }
            }
            else {
                id[i] = 0;
                cnt[i] = 0;
            }
            if (nleft && nright) {
                MaxFlow flow(nleft + nright + 2);
                int source = 0, sink = nleft + nright + 1;
                FOR(i,1,n) if (id[i]) {
                    if (i % 2 == 1) flow.addEdge(source, id[i], cnt[i]);
                    else flow.addEdge(id[i] + nleft, sink, cnt[i]);
                }
                FOR(i,1,m) {
                    int u = eu[i], v = ev[i];
                    if (u % 2 == 0) swap(u, v);
                    if (id[u] && id[v])
                        flow.addEdge(id[u], id[v] + nleft, 1000);
                }
                res += flow.getMaxFlow(source, sink);
            }
        }
        cout << res << endl;
    }
    return 0;
}
