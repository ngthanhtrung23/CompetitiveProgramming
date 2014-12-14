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

int nState, nTrans, nTerm;
bool isTerm[1011];
vector<int> ke[1011];
int res[1011][1011];
pair<int,int> edges[1011];
vector< vector<int> > paths;

void dfs(int u, vector<int> &cur) {
    if (isTerm[u]) {
        paths.push_back(cur);
    }
    for(int v : ke[u]) {
        cur.push_back(v);
        dfs(v, cur);
        cur.pop_back();
    }
}

int main() {
    freopen("suffix.in", "r", stdin);
    freopen("suffix.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nState >> nTrans >> nTerm) {
        memset(isTerm, false, sizeof isTerm);
        FOR(i,1,nTerm) {
            int u; cin >> u;
            isTerm[u] = true;
        }
        FOR(i,1,nState) ke[i].clear();
        FOR(i,1,nTrans) {
            int u, v; cin >> u >> v;
            edges[i] = make_pair(u, v);
            ke[u].push_back(v);
        }
        vector<int> cur;
        cur.push_back(1);
        dfs(1, cur);
//        for(auto path : paths) {
//            PR0(path, path.size());
//        }
        memset(res, 0, sizeof res);

        vector<int> initStr(SZ(paths) - 1, 0);
        int t = 0;
        FORD(pos,SZ(paths)-2,0) {
            int has = 0;
            int len = SZ(paths) - pos;
            for(auto path : paths) {
                if (SZ(path) < len) continue;

                int i = SZ(path) - len;
                int u = path[i], v = path[i+1];

                if (res[u][v]) has = res[u][v];
            }

            if (!has) initStr[pos] = ++t;
            else initStr[pos] = has;

            for(auto path : paths) {
                if (SZ(path) < len) continue;

                int i = SZ(path) - len;
                int u = path[i], v = path[i+1];
                
                res[u][v] = initStr[pos];
            }
        }
//        PR0(initStr, initStr.size());
        cout << initStr.size() << ' ' << t << endl;
        for(int x : initStr) cout << x << ' '; cout << endl;
        FOR(i,1,nTrans) cout << res[edges[i].first][edges[i].second] << ' '; cout << endl;
    }
    return 0;
}
