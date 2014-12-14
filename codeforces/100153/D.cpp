#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n, a[55][55];
vector< pair<int, pair<int,int> > > edges, res;
int lab[55];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);

    if (u == v) return ;

    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    }
    else {
        lab[v] = x;
        lab[u] = v;
    }
}

int d[55][55];
vector< pair<int,int> > ke[55];
bool check() {
    memset(d, -1, sizeof d);
    FOR(start,1,n) {
        queue<int> q;
        d[start][start] = 1011;
        q.push(start);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for(auto e : ke[u]) {
                int v = e.first, c = e.second;
                if (d[start][v] < 0) {
                    d[start][v] = min(d[start][u], c);
                    q.push(v);
                }
            }
        }
    }
    FOR(i,1,n) d[i][i] = 0;
    FOR(i,1,n) FOR(j,1,n) if (d[i][j] != a[i][j]) return false;
    return true;
}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        edges.clear();
        FOR(i,1,n) FOR(j,i+1,n) edges.push_back(make_pair(a[i][j], make_pair(i, j)));
        sort(edges.begin(), edges.end());
        reverse(edges.begin(), edges.end());
        memset(lab, -1, sizeof lab);

        FOR(u,1,n) ke[u].clear();
        res.clear();
        for(auto cur : edges) {
            int u = cur.second.first, v = cur.second.second;
            if (getRoot(u) != getRoot(v)) {
                res.push_back(cur);
                ke[u].push_back(make_pair(v, cur.first));
                ke[v].push_back(make_pair(u, cur.first));
                merge(u, v);
            }
        }
        if (!check()) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            cout << res.size() << endl;
            for(auto e : res)
                cout << e.second.first << ' ' << e.second.second << ' ' << e.first << endl;
        }
    }
    return 0;
}
