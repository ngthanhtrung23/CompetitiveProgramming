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

const int MN = 10111;
int n, m, nComp;
int sz[MN];
vector<int> ke[MN];

int qu[MN], visited[MN];
void bfs(int u) {
    int front = 1, end = 1; qu[1] = u;
    ++nComp;
    visited[u] = nComp;
    while (front <= end) {
        u = qu[front++];
        for(int v : ke[u]) {
            if (!visited[v]) {
                visited[v] = nComp;
                qu[++end] = v;
            }
        }
    }
    sz[nComp] = end;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case #" << test << ":\n";
        cin >> n >> m;
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        memset(visited, 0, sizeof visited);
        nComp = 0;
        FOR(i,1,n) if (!visited[i]) {
            bfs(i);
        }
        FOR(i,1,n) cout << sz[visited[i]] - 1 << ' '; cout << endl;
    }
    return 0;
}
