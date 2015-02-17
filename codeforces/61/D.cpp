
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

int n, h[MN];
vector< pair<int,int> > ke[MN];

void dfs(int u, int fu) {
    for(auto cur : ke[u]) {
        int v = cur.first;
        if (v == fu) continue;

        h[v] = h[u] + cur.second;
        dfs(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        memset(h, 0, sizeof h);
        long long sum = 0;
        FOR(i,2,n) {
            int u, v, c; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
            sum += c;
        }
        dfs(1, -1);

//        PR(h, n);

        int ln = *max_element(h+1, h+n+1);
        cout << sum * 2 - ln << endl;
    }
    return 0;
}
