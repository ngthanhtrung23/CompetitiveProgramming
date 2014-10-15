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
// Source: rng_58: http://codeforces.com/contest/277/submission/3212642
// Faster min cost max flow
// Index from 0
// NOTE!!!!!! Flow through both direction can be < 0
// --> need to be careful when trace

const long long F_INF = 1000111000111000LL;
const long long C_INF = 1000111000111000LL;

template<class Flow = long long, class Cost = long long>
struct MinCostFlow {
    int V, E;
    vector<Flow> cap;
    vector<Cost> cost;
    vector<int> to, prev;

    vector<Cost> dist, pot;
    vector<int> last, path, used;
    priority_queue< pair<Cost, int> > q;

    MinCostFlow(int V, int E) : V(V), E(0), cap(E*2,0), cost(E*2,0), to(E*2,0), prev(E*2,0),
            dist(V,0), pot(V,0), last(V, -1), path(V,0), used(V,0) {}

    int addEdge(int x, int y, Flow f, Cost c) {
        cap[E] = f; cost[E] = c; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
        cap[E] = 0; cost[E] = -c; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
        return E - 2;
    }

    pair<Flow, Cost> search(int s, int t) {
        Flow ansf = 0; Cost ansc = 0;
        REP(i,V) used[i] = false;
        REP(i,V) dist[i] = C_INF;

        dist[s] = 0; path[s] = -1; q.push(make_pair(0, s));
        while (!q.empty()) {
            int x = q.top().second; q.pop();
            if (used[x]) continue; used[x] = true;
            for(int e = last[x]; e >= 0; e = prev[e]) if (cap[e] > 0) {
                Cost tmp = dist[x] + cost[e] + pot[x] - pot[to[e]];
                if (tmp < dist[to[e]] && !used[to[e]]) {
                    dist[to[e]] = tmp;
                    path[to[e]] = e;
                    q.push(make_pair(-dist[to[e]], to[e]));
                }
            }
        }
        REP(i,V) pot[i] += dist[i];
        if (used[t]) {
            ansf = F_INF;
            for(int e=path[t]; e >= 0; e=path[to[e^1]]) ansf = min(ansf, cap[e]);
            for(int e=path[t]; e >= 0; e=path[to[e^1]]) { ansc += cost[e] * ansf; cap[e] -= ansf; cap[e^1] += ansf; }
        }
        return make_pair(ansf, ansc);
    }
    pair<Flow, Cost> minCostFlow(int s, int t) {
        Flow ansf = 0; Cost ansc = 0;
        while (1) {
            pair<Flow, Cost> p = search(s, t);
            if (!used[t]) break;
            ansf += p.first; ansc += p.second;
        }
        return make_pair(ansf, ansc);
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

        MinCostFlow<long long, double> mcf(2*n+2, (2*n+2)*(2*n+2) + 111);

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
