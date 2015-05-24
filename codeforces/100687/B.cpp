
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

bool match(string a, string b) {
    REP(i,a.length())
        if (a[i] != '?' && a[i] != b[i]) return false;
    return true;
}

string a[111];
int val[111];
int n;
string stu;

string mp[1000111], str[1000111];
int ver[1000111];
int start, target;

const int LOW_BOUND = 20110000;
const int UP_BOUND = 20159999;

int main() {
    FOR(id,LOW_BOUND,UP_BOUND) {
        int v = n + id - LOW_BOUND + 1;
        stringstream ss; ss << id;

        mp[id - LOW_BOUND] = ss.str();
    }

    ios :: sync_with_stdio(false);
    int id;
    while (cin >> n >> id) {
        stu = mp[id - LOW_BOUND];
        FOR(i,1,n) cin >> a[i] >> val[i];

        int cur = 0;
        start = cur++;
        FOR(i,1,n) cur++;

        FOR(id,LOW_BOUND,UP_BOUND) {
            bool ok = false;
            FOR(i,1,n) if (match(a[i], mp[id - LOW_BOUND])) {
                str[cur] = mp[id - LOW_BOUND];
                ver[id - LOW_BOUND] = cur++;
                break;
            }
        }
        target = cur++;
//        DEBUG(cur);

//        FOR(i,n+1,target-1) {
//            DEBUG(str[i]);
//        }

        int res = 0;
        FOR(i,1,n) if (match(a[i], stu)) {
            MaxFlow flow(cur);

            FOR(left,1,n) if (left != i) flow.addEdge(start, left, 1);

            FOR(left,1,n) FOR(right,n+1,target-1) {
                if (match(a[left], str[right])) {
//                    if (DEBUG) cout << left << ' ' << right << endl;
                    flow.addEdge(left, right, 1);
                }
            }
            FOR(right,n+1,target-1)
                if (str[right] != stu)
                    flow.addEdge(right, target, 1);

            if (flow.getMaxFlow(start, target) == n-1) {
                res = max(res, val[i]);
            }
        }
        cout << res << endl;
    }
    return 0;
}
