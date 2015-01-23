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
vector< pair<int,int> > ke[MN];
int d[MN], n, m;
pair<int,int> a[MN];
int f[MN], tr[MN];

set< pair<int,int> > path;

void trace(int v) {
    if (v == 1) return ;

    int u = tr[v];
    trace(u);
    path.insert(make_pair(u, v));
    path.insert(make_pair(v, u));
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v, z;
            cin >> u >> v >> z;
            ke[u].push_back(make_pair(v, z));
            ke[v].push_back(make_pair(u, z));
        }
        memset(d, -1, sizeof d);

        queue<int> qu;
        qu.push(1); d[1] = 0;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(auto e : ke[u]) {
                int v = e.first;
                if (d[v] < 0) {
                    d[v] = d[u] + 1;
                    qu.push(v);
                }
            }
        }
//        PR(d, n);

        FOR(i,1,n) a[i] = make_pair(d[i], i);
        sort(a+1, a+n+1);

        f[1] = 0;
        FOR(i,2,n) {
            int u = a[i].second;
            f[u] = -1;
            for(auto e : ke[u]) {
                int v = e.first, z = e.second;
                if (d[v] + 1 == d[u]) {
                    int now = f[v] + z;
                    if (now > f[u]) {
                        f[u] = now;
                        tr[u] = v;
                    }
                }
            }
        }
//        PR(f, n);
//        PR(tr, n);
        path.clear();
        trace(n);

        vector< pair< pair<int,int>, int > > res;

        FOR(u,1,n) {
            for(auto e : ke[u]) {
                int v = e.first, z = e.second;
                if (u > v) continue;
                if (path.count(make_pair(u, v))) {
                    if (z == 0) res.push_back(make_pair(make_pair(u, v), 1));
                }
                else {
                    if (z == 1) res.push_back(make_pair(make_pair(u, v), 0));
                }
            }
        }

        cout << res.size() << "\n";
        for(auto x : res)
            cout << x.first.first << ' ' << x.first.second << ' ' << x.second << "\n";
    }
    return 0;
}

