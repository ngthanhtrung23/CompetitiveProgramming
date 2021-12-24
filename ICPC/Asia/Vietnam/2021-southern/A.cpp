#include "bits/stdc++.h"
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int r) {
    return uniform_int_distribution<int> (0, r-1)(rng);
}

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 211;

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
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

struct GomoryHu {
    int ok[MN], cap[MN][MN];
    int answer[MN][MN], parent[MN];
    int n;
    MaxFlow flow;

    GomoryHu(int _n) : n(_n), flow(_n) {
        for(int i = 0; i < n; ++i) ok[i] = parent[i] = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                cap[i][j] = 0, answer[i][j] = INF;
    }

    void addEdge(int u, int v, int c) {
        cap[u][v] += c;
    }

    void calc() {
        for(int i = 1; i <= n-1; ++i) {
            flow = MaxFlow(n);
            REP(u,n) REP(v,n)
                if (cap[u][v])
                    flow.addEdge(u, v, cap[u][v]);

            int f = flow.getMaxFlow(i, parent[i]);

            bfs(i);
            for(int j = i+1; j < n; ++j)
                if (ok[j] && parent[j]==parent[i])
                    parent[j]=i;
            
            answer[i][parent[i]] = answer[parent[i]][i] = f;
            for(int j = 0; j < i; ++j)
                answer[i][j]=answer[j][i]=min(f,answer[parent[i]][j]);
        }
    }
    void bfs(int start) {
        memset(ok,0,sizeof ok);
        queue<int> qu;
        qu.push(start);
        while (!qu.empty()) {
            int u=qu.front(); qu.pop();
            for(int xid = 0; xid < (int) flow.g[u].size(); ++xid) {
                int id = flow.g[u][xid];
                int v = flow.e[id].b, fl = flow.e[id].flow, c = flow.e[id].cap;
                if (!ok[v] && fl < c) {
                    ok[v]=1;
                    qu.push(v);
                }
            }
        }
    }
};

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n; cin >> n;
        GomoryHu g(n);
        REP(i,n) REP(j,n) {
            int cap; cin >> cap;
            if (cap) g.addEdge(i, j, cap);
        }
        g.calc();

        cout << "Case #" << test << ":\n";
        REP(i,n) {
            REP(j,n) {
                int res = g.answer[i][j];
                if (res == INF) res = 0;
                cout << res << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
