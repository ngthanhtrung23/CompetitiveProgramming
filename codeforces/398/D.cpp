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

const int SQRTN = 311;
const int MN = 50111;

int online[MN], cnt[MN];
set< int > ke[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int nUser, nRel, nQuery;
    while (cin >> nUser >> nRel >> nQuery) {
        int nOnl; cin >> nOnl;
        memset(online, 0, sizeof online);
        memset(cnt, 0, sizeof cnt);
        while (nOnl--) {
            int u; cin >> u;
            online[u] = 1;
        }
        while (nRel--) {
            int u, v; cin >> u >> v;
            if (ke[u].size() < SQRTN) {
                ke[u].insert(v);
                cnt[v] += online[u];
            }
            else {
                ke[v].insert(u);
                cnt[u] += online[v];
            }
        }
        while (nQuery--) {
            char typ; cin >> typ;
            if (typ == 'O') {
                int u; cin >> u;
                online[u] = 1;
                for(auto v : ke[u])
                    cnt[v]++;
            }
            else if (typ == 'F') {
                int u; cin >> u;
                online[u] = 0;
                for(auto v : ke[u])
                    cnt[v]--;
            }
            else if (typ == 'A') {
                int u, v; cin >> u >> v;
                if (ke[u].size() < SQRTN) {
                    ke[u].insert(v);
                    cnt[v] += online[u];
                }
                else {
                    ke[v].insert(u);
                    cnt[u] += online[v];
                }
            }
            else if (typ == 'D') {
                int u, v; cin >> u >> v;
                if (ke[u].count(v)) {
                    ke[u].erase(v);
                    cnt[v] -= online[u];
                }
                else {
                    ke[v].erase(u);
                    cnt[u] -= online[v];
                }
            }
            else {
                int u; cin >> u;
                int res = cnt[u];
                for(auto v : ke[u])
                    res += online[v];
                cout << res << "\n";
            }
        }
    }
    return 0;
}
