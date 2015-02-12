
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

const int MN = 1<<17;

int deg[MN], sum[MN];
vector<int> ke[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        REP(i,n) ke[i].clear();
        set< pair<int,int> > s;
        REP(i,n) {
            cin >> deg[i] >> sum[i];
            s.insert(make_pair(deg[i], i));
        }

        int m = 0;
        while (!s.empty()) {
            int u = s.begin()->second;
            s.erase(s.begin());

            if (deg[u] == 0) continue;
            if (deg[u] == 1) {
                int v = sum[u];
                ke[u].push_back(v);
                ++m;
                --deg[u];

                s.erase(make_pair(deg[v], v));
                --deg[v];
                sum[v] ^= u;
                s.insert(make_pair(deg[v], v));
            }
        }
        cout << m << "\n";
        REP(i,n) if (ke[i].size()) {
            for(auto x : ke[i])
                cout << i << ' ' << x << "\n";
        }
    }
    return 0;
}
