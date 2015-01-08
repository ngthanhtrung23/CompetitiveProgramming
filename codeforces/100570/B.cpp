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

const int MN = 100111;
const long long oo = 1000111000111000111LL;

int n, m, c, start, q;
vector< pair<int, pair<int,int> > > ke[MN];
long long d[2][MN];
int trace[2][MN];

void dijkstra() {
    set< pair<long long,pair<int,int> > > s;
    FOR(i,1,n) d[0][i] = d[1][i] = oo;
    d[0][start] = 0; trace[0][start] = -1;
    s.insert(make_pair(0, make_pair(0, start)));

    while (!s.empty()) {
        auto it = *s.begin();
        s.erase(s.begin());

        long long l = it.first;
        int t = it.second.first, u = it.second.second;
        if (l != d[t][u]) continue;
        
        for(auto e : ke[u]) {
            int v = e.first, w = e.second.first, c = e.second.second;
            if (trace[t][u] != c) {
                if (d[0][v] >= d[t][u] + w) {
                    // We must make sure that trace[0][v] != trace[1][v]
                    if (trace[0][v] != c) {
                        d[1][v] = d[0][v];
                        trace[1][v] = trace[0][v];
                        s.insert(make_pair(d[1][v], make_pair(1, v)));
                    }

                    d[0][v] = d[t][u] + w;
                    trace[0][v] = c;
                    s.insert(make_pair(d[0][v], make_pair(0, v)));
                }
                else if (d[1][v] > d[t][u] + w && trace[0][v] != c) {
                    d[1][v] = d[t][u] + w;
                    trace[1][v] = c;
                    s.insert(make_pair(d[1][v], make_pair(1, v)));
                }
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m >> c) {
        FOR(i,1,n) ke[i].clear();
        while (m--) {
            int u, v, w, c; cin >> u >> v >> w >> c;
            ke[u].push_back(make_pair(v, make_pair(w, c)));
        }
        cin >> start >> q;
        dijkstra();
        while (q--) {
            int u; cin >> u;
            if (d[0][u] == oo) d[0][u] = -1;
            cout << d[0][u] << "\n";
        }
    }
    return 0;
}
