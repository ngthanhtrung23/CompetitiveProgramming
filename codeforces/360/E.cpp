
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

const int MN = 100111;
struct Edge {
    int from, to;
    int cost;
    int l, r;
} edges[MN];

int n, m, k;
int s1, s2, t;
ll f[2][MN];
vector<int> ke[MN];

void dijkstra(int t, int start) {
    FOR(i,1,n) f[t][i] = 1e18;
    set< pair<ll,int> > all;
    all.insert(make_pair(0, start));
    f[t][start] = 0;

    while (!all.empty()) {
        int u = all.begin()->second;
        ll l = all.begin()->first;
        all.erase(all.begin());

        if (l != f[t][u]) continue;

        for(int eid : ke[u]) {
            int v = edges[eid].to;
            if (f[t][v] > f[t][u] + edges[eid].cost) {
                f[t][v] = f[t][u] + edges[eid].cost;
                all.insert(make_pair(f[t][v], v));
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m >> k) {
        cin >> s1 >> s2 >> t;

        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int a, b, c; cin >> a >> b >> c;
            edges[i].from = a;
            edges[i].to = b;
            edges[i].cost = c;
            edges[i].l = edges[i].r = c;

            ke[a].push_back(i);
        }
        FOR(i,m+1,m+k) {
            int a, b, l, r; cin >> a >> b >> l >> r;
            edges[i].from = a;
            edges[i].to = b;
            edges[i].cost = r;
            edges[i].l = l;
            edges[i].r = r;

            ke[a].push_back(i);
        }

        bool changed = true;
        while (changed) {
            changed = false;
            dijkstra(0, s1);
            dijkstra(1, s2);

//            cout << "-----" << endl;
//            FOR(i,1,m+k) cout << edges[i].from << ' ' << edges[i].to << ' ' << edges[i].cost << endl;
//            PR(f[0], n);
//            PR(f[1], n);

            FOR(i,1,m+k) {
                int u = edges[i].from, v = edges[i].to;
                if (f[0][u] < f[1][u] && edges[i].cost != edges[i].l) {
                    changed = true;
                    edges[i].cost = edges[i].l;
                }
                if (f[0][u] > f[1][u] && edges[i].cost != edges[i].r) {
                    changed = true;
                    edges[i].cost = edges[i].r;
                }
            }
        }
        if (f[0][t] < f[1][t]) {
            cout << "WIN" << endl;
            FOR(i,m+1,m+k) cout << edges[i].cost << ' '; cout << endl;
        }
        else if (f[0][t] == f[1][t]) {
            cout << "DRAW" << endl;
            FOR(i,m+1,m+k) cout << edges[i].cost << ' '; cout << endl;
        }
        else {
            cout << "LOSE" << endl;
        }
    }
}
