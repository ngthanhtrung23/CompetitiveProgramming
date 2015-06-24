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
const long long MOD = 1e9 + 7;

vector<pair<int,int> > ke[MN];
int n, m, color[MN];
bool bad;

void dfs(int u, int c) {
    color[u] = c;
    for(auto e : ke[u]) {
        int v = e.first;
        if (color[v] < 0) {
            if (e.second == 1) dfs(v, c);
            else dfs(v, 1 - c);
        }
        else {
            if (e.second == 1 && color[u] != color[v]) bad = true;
            if (e.second == 0 && color[u] == color[v]) bad = true;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,m) {
            int u, v, t; cin >> u >> v >> t;
            ke[u].push_back(make_pair(v, t));
            ke[v].push_back(make_pair(u, t));
        }
        memset(color, -1, sizeof color);
        int cnt = 0;
        bad = false;
        FOR(i,1,n) if (color[i] < 0) {
            ++cnt;
            dfs(i, 0);
        }
        if (bad) cout << 0 << endl;
        else {
            long long res = 1;
            FOR(i,1,cnt-1) res = res * 2 % MOD;
            cout << res << endl;
        }
    }
}

