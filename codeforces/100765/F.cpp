
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

const int MN = 2011;

int f[MN], g[MN];
vector< pair<int,int> > ke[MN];
int n, X, Y;

void ijk(int X, int f[]) {
    FOR(i,1,n) f[i] = 1000111000;
    f[X] = 0;
    set< pair<int,int> > s;
    s.insert(make_pair(0, X));
    while (!s.empty()) {
        int l = s.begin()->first, u = s.begin()->second;
        s.erase(s.begin());
        if (f[u] != l) continue;

        for(auto e : ke[u]) {
            int v = e.first, c = e.second;
            if (f[v] > f[u] + c) {
                f[v] = f[u] + c;
                s.insert(make_pair(f[v], v));
            }
        }
    }
}

int res[MN];
vector< pair<pair<int,int>,int> > events;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> X >> Y) {
        FOR(i,1,n) ke[i].clear();

        int m; cin >> m;
        while (m--) {
            int c, u, v; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        ijk(X, f);
        ijk(Y, g);
//        PR(f, n);
//        PR(g, n);

        FOR(i,1,n) {
            res[i] = 0;
            if (f[i] + g[i] != f[Y]) continue;

            FOR(j,1,n) if (f[j] + g[j] == f[Y] && f[j] == f[i])
                ++res[i];
        }

        events.clear();
        FOR(i,1,n) {
            if (f[i] + g[i] == f[Y])
                events.push_back(make_pair(make_pair(f[i], 0), i));
        }
        FOR(u,1,n) {
            for(auto e : ke[u]) {
                int v = e.first, c = e.second;
                if (f[u] + c + g[v] == f[Y]) {
                    events.push_back(make_pair(make_pair(f[u], 1), u));
                    events.push_back(make_pair(make_pair(f[v], -1), v));
                }
            }
        }
        sort(events.begin(), events.end());

        int cur = 0;
        for(auto e : events) {
            if (e.first.second == 1) ++cur;
            else if (e.first.second == -1) --cur;
            else {
                res[ e.second ] += cur;
            }
        }

        FOR(i,1,n) {
            if (f[i] + g[i] != f[Y]) res[i] = 0;
        }
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
}
