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

const double INF = 1e15;
const double EPS = 1e-6;
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
        last[from] = t; ++t;
        edges.push_back(Edge(from, 0, -cost, last[to]));
        last[to] = t; ++t;
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
            if (dis[x] > d + EPS) continue;
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
            if (edges[it].cap && !visited[edges[it].to] && fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < EPS) {
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

        if (d > 1e10) return false;
        REP(i,n) if (visited[i])
            dis[i] += d;
        return true;
    }
};

int x[411], y[411];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(9);
    int n;
    while (cin >> n) {
        REP(i,n) cin >> x[i] >> y[i];
        int ymax = *max_element(y, y+n);
        int cnt_max = 0;
        REP(i,n) if (y[i] == ymax) ++cnt_max;

        if (cnt_max > 1) {
            cout << -1 << endl;
            continue;
        }

        MinCostFlow<long long, double> mcf(2*n+2);

        REP(i,n) if (y[i] != ymax) mcf.addEdge(2*n, i, 1, 0);
        REP(i,n) mcf.addEdge(n+i, 2*n+1, 2, 0);

        REP(i,n) REP(j,n) if (y[i] < y[j]) {
            double dx = x[i] - x[j], dy = y[i] - y[j];
            mcf.addEdge(i, n+j, 1, sqrt(dx*dx + dy*dy));
        }
        pair<long long, double> ans = mcf.minCostFlow(2*n, 2*n+1);
        if (ans.first != n-1) cout << -1 << endl;
        else cout << ans.second << endl;
    }
    return 0;
}

