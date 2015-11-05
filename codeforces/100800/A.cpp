
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
#define double long double
using namespace std;

struct Point {
    ll x, y;
    ll h;

    Point() { x = y = 0; }

    void read() { cin >> x >> y >> h; }
} a[555];

int nHill, nSpring, nTown;
double maxLen;
int spring[55], town[55];
double dist[555][555];

template<class Flow=int, class Cost=int>
struct MinCostFlow {
    const Flow INF_FLOW = 1000111000;
    const Cost INF_COST = 1e20;

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
                if (!findFlow(S, INF_FLOW)) break;
            }
            if (!modifyLabel()) break;
        }
        return make_pair(totalFlow, totalCost);
    }

private:
    void SPFA() {
        REP(i,n) dis[i] = INF_COST;
        priority_queue< pair<Cost,int> > Q;
        Q.push(make_pair(dis[S]=0, S));
        while (!Q.empty()) {
            int x = Q.top().second;
            Cost d = -Q.top().first;
            Q.pop();
            if (dis[x] > d + 1e-6) continue;
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
            if (edges[it].cap && !visited[edges[it].to]
                    && fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < 1e-6) {
                Flow tmp = findFlow(edges[it].to, min(now, edges[it].cap));
                edges[it].cap -= tmp;
                edges[it ^ 1].cap += tmp;
                now -= tmp;
                if (!now) break;
            }
        return flow - now;
    }

    bool modifyLabel() {
        Cost d = INF_COST;
        REP(i,n) if (visited[i])
            for(int it = last[i]; it >= 0; it = edges[it].next)
                if (edges[it].cap && !visited[edges[it].to])
                    d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

        if (d > INF_COST / 10) return false;
        REP(i,n) if (visited[i])
            dis[i] += d;
        return true;
    }
};

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nHill >> nSpring >> nTown >> maxLen) {
        FOR(i,1,nHill) a[i].read();
        FOR(i,1,nSpring) cin >> spring[i];
        FOR(i,1,nTown) cin >> town[i];

        FOR(i,1,nHill) FOR(j,1,nHill) {
            if (i == j) dist[i][j] = 0;
            else if (a[i].h > a[j].h) {
                double cur = sqrt(
                        sqr(a[i].x - a[j].x)
                        + sqr(a[i].y - a[j].y)
                        + sqr(a[i].h - a[j].h)
                        );
                if (cur > maxLen + 1e-6) cur = 1e12;
                dist[i][j] = cur;
            }
            else dist[i][j] = 1e12;
        }
        FOR(k,1,nHill)
            FOR(i,1,nHill) FOR(j,1,nHill)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        int s = 0, t = nSpring + nTown + 1;
        MinCostFlow<int,double> flow(t + 1);

        FOR(i,1,nSpring) flow.addEdge(s, i, 1, 0);
        FOR(i,1,nTown) flow.addEdge(nSpring+i, t, 1, 0);
        FOR(i,1,nSpring) FOR(j,1,nTown) {
            int u = spring[i], v = town[j];
            if (dist[u][v] < 1e11) {
                flow.addEdge(i, nSpring+j, 1, dist[u][v]);
            }
        }
        pair<int,double> res = flow.minCostFlow(s, t);
        if (res.first == nTown) {
            cout << (fixed) << setprecision(9) << res.second << endl;
        }
        else cout << "IMPOSSIBLE" << endl;
    }
}
