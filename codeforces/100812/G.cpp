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
using namespace std;

const int MN = 100111;
const ll INF = 1000111000111000LL;

int n, m, color[MN];
vector< pair<int,int> > ke[MN];
ll f[MN];
int root[MN];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) scanf("%d", &color[i]);
        ll res = INF;
        int saveu, savev;
        FOR(i,1,m) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));

            if (color[u] == 1 && color[v] == 1) {
                if (c < res) {
                    res = c;
                    saveu = u;
                    savev = v;
                }
            }
        }

        FOR(i,1,n) f[i] = INF;
        set< pair<ll, int> > all;
        FOR(i,1,n) if (color[i] == 1) {
            root[i] = i;
            f[i] = 0;
            all.insert(make_pair(0, i));
        }

        while (!all.empty()) {
            auto p = *all.begin(); all.erase(all.begin());
            ll l = p.first;
            int u = p.second;
            if (l != f[u]) continue;

            for(auto p : ke[u]) {
                int v = p.first;
                ll c = p.second;

                if (root[v] != root[u]) {
                    ll cur = f[v] + f[u] + c;
                    if (cur < res) {
                        res = cur;
                        saveu = root[u];
                        savev = root[v];
                    }
                }

                if (f[v] > f[u] + c) {
                    f[v] = f[u] + c;
                    root[v] = root[u];
                    all.insert(make_pair(f[v], v));
                }
            }
        }

        if (res == INF) cout << "No luck at all" << endl;
        else cout << res << endl << saveu << ' ' << savev << endl;
    }
}
