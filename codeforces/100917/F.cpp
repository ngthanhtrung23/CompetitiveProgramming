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

const int MN = 311;
const int INF = 1000111000;

int c[MN][MN], n, res[MN];
vector<int> ke[MN];
int f[MN], tr[MN], h[MN];

void dijkstra(int start) {
    FOR(i,1,n) f[i] = INF;
    f[start] = 0;
    h[start] = 0;
    tr[start] = start;
    set< pair<int,int> > s; s.insert(make_pair(0, start));
    while (!s.empty()) {
        int l = s.begin()->first;
        int u = s.begin()->second;
        s.erase(s.begin());

        if (l != f[u]) continue;

        for(int v : ke[u]) {
            if (f[v] > f[u] + c[u][v]) {
                f[v] = f[u] + c[u][v];
                h[v] = h[u] + 1;
                tr[v] = u;
                s.insert(make_pair(f[v], v));
            }
        }
    }

    FOR(i,1,n) FOR(j,i+1,n) if (c[i][j] > 0) {
        if (tr[i] == j || tr[j] == i) continue;

        int u = i, v = j;
        if (h[u] > h[v]) swap(u, v);

        while (h[v] > h[u]) {
            v = tr[v];
        }
        while (u != v) {
            u = tr[u];
            v = tr[v];
        }
        if (u == start) {
            res[start] = min(res[start], c[i][j] + f[i] + f[j]);
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) FOR(j,1,n) {
            cin >> c[i][j];
            if (c[i][j] > 0) {
                ke[i].push_back(j);
            }
        }
        FOR(i,1,n) res[i] = INF;

        FOR(i,1,n) dijkstra(i);

        FOR(i,1,n) if (res[i] == INF) res[i] = -1;
        FOR(i,1,n) cout << res[i] << '\n';
    }
}
