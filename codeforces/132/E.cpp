#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int INF = 1000111000;
template<class Flow=int, class Cost=int>
struct MinCostFlow {
    int n, t, S, T;
    Flow totalFlow;
    Cost totalCost;
    vector<int> last, visited;
    vector<Cost> dis;
    struct Edge {
        int to;
        Flow cap;
        Cost cost;
        int next;
        Edge(int to, Flow cap, Cost cost, int next) :
                to(to), cap(cap), cost(cost), next(next) {}
    };
    vector<Edge> edges;

    MinCostFlow(int n) : n(n), t(0), totalFlow(0), totalCost(0), last(n, -1), visited(n, 0), dis(n, 0) {
        edges.clear();
    }

    int addEdge(int from, int to, Flow cap, Cost cost) {
        edges.push_back(Edge(to, cap, cost, last[from]));
        last[from] = t++;
        edges.push_back(Edge(from, 0, -cost, last[to]));
        last[to] = t++;
        return t - 2;
    }

    pair<Flow, Cost> minCostFlow(int _S, int _T) {
        S = _S; T = _T;
        SPFA();
        while (1) {
            while (1) {
                REP(i,n) visited[i] = 0;
                if (!findFlow(S, INF)) break;
            }
            if (!modifyLabel()) break;
        }
        return make_pair(totalFlow, totalCost);
    }

private:
    void SPFA() {
        REP(i,n) dis[i] = INF;
        priority_queue< pair<Cost,int> > Q;
        Q.push(make_pair(dis[S]=0, S));
        while (!Q.empty()) {
            int x = Q.top().second;
            Cost d = -Q.top().first;
            Q.pop();
            // For double: dis[x] > d + EPS
            if (dis[x] != d) continue;
            for(int it = last[x]; it >= 0; it = edges[it].next)
                if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
                    Q.push(make_pair(-(dis[edges[it].to] = d + edges[it].cost), edges[it].to));
        }
        REP(i,n) dis[i] = dis[T] - dis[i];
    }

    Flow findFlow(int x, Flow flow) {
        if (x == T) {
            totalCost += dis[S] * flow;
            totalFlow += flow;
            return flow;
        }
        visited[x] = 1;
        Flow now = flow;
        for(int it = last[x]; it >= 0; it = edges[it].next)
            // For double: fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < EPS
            if (edges[it].cap && !visited[edges[it].to] && dis[edges[it].to] + edges[it].cost == dis[x]) {
                Flow tmp = findFlow(edges[it].to, min(now, edges[it].cap));
                edges[it].cap -= tmp;
                edges[it ^ 1].cap += tmp;
                now -= tmp;
                if (!now) break;
            }
        return flow - now;
    }

    bool modifyLabel() {
        Cost d = INF;
        REP(i,n) if (visited[i])
            for(int it = last[i]; it >= 0; it = edges[it].next)
                if (edges[it].cap && !visited[edges[it].to])
                    d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

        // For double: if (d > INF / 10)     INF = 1e20
        if (d == INF) return false;
        REP(i,n) if (visited[i])
            dis[i] += d;
        return true;
    }
};



const int MN = 311;
int n, m, a[MN];
char var[MN];
int edgeId[MN][MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];

        MinCostFlow<int,int> flow(2 * (m+n) + 2);

        int sink = 2 * (m+n) + 1;
        FOR(i,1,m+n) flow.addEdge(0, i, 1, 0);
        FOR(i,m+n+1,sink-1) flow.addEdge(i, sink, 1, 0);

        memset(edgeId, -1, sizeof edgeId);

        FOR(i,1,m+n)
            if (i <= m) {
                FOR(j,m+1,m+n)
                    edgeId[i][j] = flow.addEdge(i, j+(m+n), 1, __builtin_popcount(a[j-m]));
            } else {
                FOR(j,i+1,m+n) {
                    int cost = (a[i-m] == a[j-m]) ? 0 : __builtin_popcount(a[j-m]);
                    edgeId[i][j] = flow.addEdge(i, j+(m+n), 1, cost);
                }
            }

        pair<int,int> res = flow.minCostFlow(0, sink);
        vector< pair<int, pair<int,int> > > statements;

        FOR(j,m+1,m+n) {
            int v = m + n + j;
            FOR(i,1,m+n)
                if (edgeId[i][j] >= 0 && !flow.edges[edgeId[i][j]].cap) {
                    if (i <= m) {
                        statements.push_back(make_pair(0, make_pair(i, a[j - m])));
                        statements.push_back(make_pair(1, make_pair(i, 0)));
                        var[j - m] = i;
                    } else {
                        var[j - m] = var[i - m];
                        if (a[i - m] == a[j - m]) {
                            statements.push_back(make_pair(1, make_pair(var[j-m], 0)));
                        } else {
                            statements.push_back(make_pair(0, make_pair(var[j - m], a[j - m])));
                            statements.push_back(make_pair(1, make_pair(var[j-m], 0)));
                        }
                    }
                }
        }
        cout << statements.size() << ' ' << res.second << "\n";
        REP(i,statements.size()) {
            if (statements[i].first == 0) {
                cout << (char) (statements[i].second.first - 1 + 'a') << '=' << statements[i].second.second << "\n";
            }
            else {
                cout << "print(" << (char) (statements[i].second.first - 1 + 'a') << ")\n";
            }
        }
    }
}
