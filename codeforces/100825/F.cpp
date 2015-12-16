
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
const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
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

int nState, nRaw, nFactory, nTrans;
map<string,int> id;
int raw[611], factory[611];
vector<int> trans[1011];

int getId(string t) {
    if (!id.count(t)) {
        int cur = SZ(id) + 1;
        id[t] = cur;
    }
    return id[t];
}
int getNext() {
    string t; cin >> t;
    return getId(t);
}

int transIn[1011], transOut[1011], source, sink;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> nState >> nRaw >> nFactory >> nTrans) {
        id.clear();
        FOR(i,1,nRaw) raw[i] = getNext();
        FOR(i,1,nFactory) factory[i] = getNext();
        FOR(i,1,nTrans) {
            int k; cin >> k;
            trans[i].resize(k);
            REP(j,k) trans[i][j] = getNext();
        }
        int nVertex = nState;
        source = 0;

        FOR(i,1,nTrans) {
            transIn[i] = ++nVertex;
            transOut[i] = ++nVertex;
        }
        sink = ++nVertex;
        MaxFlow flow(nVertex + 1);

        FOR(i,1,nRaw) flow.addEdge(source, raw[i], 1);
        FOR(i,1,nFactory) flow.addEdge(factory[i], sink, 1);

        FOR(i,1,nTrans) {
            flow.addEdge(transIn[i], transOut[i], 1);
            for(int x : trans[i]) {
                flow.addEdge(x, transIn[i], 1);
                flow.addEdge(transOut[i], x, 1);
            }
        }
        cout << flow.getMaxFlow(source, sink) << endl;
    }
}
