
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

#define _MAX_COST INT_MAX
#define _MAX_FLOW INT_MAX

template<class Flow = int, class Cost = int>
struct MinCostFlow {
    struct Edge {
        int t;
        Flow f;
        Cost c;
        Edge*next, *rev;
        Edge(int _t, Flow _f, Cost _c, Edge*_next) :
                t(_t), f(_f), c(_c), next(_next) {
        }
    };
    vector<Edge*> E;

    int addV() {
        E.push_back((Edge*) 0);
        return E.size() - 1;
    }
    Edge* makeEdge(int s, int t, Flow f, Cost c) {
        return E[s] = new Edge(t, f, c, E[s]);
    }
    Edge* addEdge(int s, int t, Flow f, Cost c) {
        Edge*e1 = makeEdge(s, t, f, c), *e2 = makeEdge(t, s, 0, -c);
        e1->rev = e2, e2->rev = e1;
        return e1;
    }
    pair<Flow, Cost> minCostFlow(int vs, int vt) {
        int n = E.size();
        Flow flow = 0;
        Cost cost = 0;
        const Cost MAX_COST = _MAX_COST;
        const Flow MAX_FLOW = _MAX_FLOW;
        for (;;) {
            vector<Cost> dist(n, MAX_COST);
            vector<Flow> am(n, 0);
            vector<Edge*> prev(n);
            vector<bool> inQ(n, false);
            queue<int> que;

            dist[vs] = 0;
            am[vs] = MAX_FLOW;
            que.push(vs);
            inQ[vs] = true;

            while (!que.empty()) {
                int u = que.front();
                Cost c = dist[u];
                que.pop();
                inQ[u] = false;
                for (Edge*e = E[u]; e; e = e->next)
                    if (e->f > 0) {
                        Cost nc = c + e->c;
                        if (nc < dist[e->t]) {
                            dist[e->t] = nc;
                            prev[e->t] = e;
                            am[e->t] = min(am[u], e->f);
                            if (!inQ[e->t]) {
                                que.push(e->t);
                                inQ[e->t] = true;
                            }
                        }
                    }
            }

            if (dist[vt] == MAX_COST) // careful with double
                break;
            Flow by = am[vt];
            int u = vt;
            flow += by;
            cost += by * dist[vt];
            while (u != vs) {
                Edge*e = prev[u];
                e->f -= by;
                e->rev->f += by;
                u = e->rev->t;
            }
        }
        return make_pair(flow, cost);
    }
};


#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

const int MN = 211;
int a[MN][MN], id[MN][MN];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("domino.in", "r", stdin);
    freopen("domino.out", "w", stdout);

    int m, n, k;
    while (cin >> m >> n >> k) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        int x = 0, y = 1, z = 2, cur = 3;
        FOR(i,1,m) FOR(j,1,n) {
            id[i][j] = cur++;
        }

        MinCostFlow<int,ll> flow;
        REP(i,cur) flow.addV();

        flow.addEdge(x, y, k, 0);
        FOR(i,1,m) FOR(j,1,n) {
            if ((i + j) % 2 == 0) {
                flow.addEdge(y, id[i][j], 1, 0);

                REP(dir,4) {
                    int ii = i + di[dir], jj = j + dj[dir];
                    if (ii < 1 || ii > m || jj < 1 || jj > n) continue;

                    flow.addEdge(id[i][j], id[ii][jj],
                            1, -a[i][j] * a[ii][jj]);
                }
            }
            else {
                flow.addEdge(id[i][j], z, 1, 0);
            }
        }
        auto p = flow.minCostFlow(x, z);
        assert(p.first == k);
        cout << -p.second << endl;
    }
}
