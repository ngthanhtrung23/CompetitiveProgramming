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

template<class Flow=int, class Cost=ll>
struct MinCostFlow {
    const Flow INF_FLOW = 1000111000;
    const Cost INF_COST = 1000111000111000LL;

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
            // For double: dis[x] > d + EPS
            if (dis[x] != d) continue;
            for(int it = last[x]; it >= 0; it = edges[it].next)
                if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
                    Q.push(make_pair(-(dis[edges[it].to] = d + edges[it].cost), edges[it].to));
        }
        Cost disT = dis[T]; REP(i,n) dis[i] = disT - dis[i];
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
        Cost d = INF_COST;
        REP(i,n) if (visited[i])
            for(int it = last[i]; it >= 0; it = edges[it].next)
                if (edges[it].cap && !visited[edges[it].to])
                    d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

        // For double: if (d > INF_COST / 10)     INF_COST = 1e20
        if (d == INF_COST) return false;
        REP(i,n) if (visited[i])
            dis[i] += d;
        return true;
    }
};


struct Point {
    int x, y;
    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }
} buildings[111], shelters[111];

int dist(const Point& a, const Point& b) {
    return 1 + abs(a.x - b.x) + abs(a.y - b.y);
}

int nBuilding, nShelter;
int buildingSZ[111], shelterSZ[111];

int res[111][111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("evacuate.in", "r", stdin);
    freopen("evacuate.out", "w", stdout);
    while (cin >> nBuilding >> nShelter) {
        FOR(i,1,nBuilding) cin >> buildings[i] >> buildingSZ[i];
        FOR(i,1,nShelter) cin >> shelters[i] >> shelterSZ[i];
        ll cityPlan = 0;
        FOR(i,1,nBuilding) FOR(j,1,nShelter) {
            ll e; cin >> e;
            cityPlan += dist(buildings[i], shelters[j]) * e;
        }
//        DEBUG(cityPlan);

        MinCostFlow<int,ll> flow(nBuilding + nShelter + 2);
        int t = nBuilding + nShelter + 1;
        FOR(i,1,nBuilding) flow.addEdge(0, i, buildingSZ[i], 0);
        FOR(i,1,nShelter) flow.addEdge(nBuilding + i, t, shelterSZ[i], 0);
        FOR(i,1,nBuilding) FOR(j,1,nShelter)
            flow.addEdge(i, nBuilding+j, 1000111, dist(buildings[i], shelters[j]));
        auto p = flow.minCostFlow(0, t);
//        DEBUG(p.first);
//        DEBUG(p.second);

        if (p.second == cityPlan) cout << "OPTIMAL" << endl;
        else {
            cout << "SUBOPTIMAL" << endl;
            memset(res, 0, sizeof res);
            FOR(i,1,nBuilding) {
                for(int eid = flow.last[i]; eid >= 0; eid = flow.edges[eid].next) {
                    int to = flow.edges[eid].to;
                    if (nBuilding < to && to <= nBuilding + nShelter) {
                        int fl = 1000111 - flow.edges[eid].cap;
                        if (fl > 0) res[i][to - nBuilding] = fl;
                    }
                }
            }
            FOR(i,1,nBuilding) {
                FOR(j,1,nShelter) cout << res[i][j] << ' ';
                cout << endl;
            }
        }
    }
}
