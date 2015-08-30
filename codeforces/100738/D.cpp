
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
using namespace std;

const int MN = 200111;

int n, deg[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        set< pair<int,int> > all;
        int sum = 0;
        FOR(i,1,n) {
            scanf("%d", &deg[i]);
            all.insert(make_pair(deg[i], i));
            sum += deg[i];
        }
        if (sum != 2 * n - 2 || *min_element(deg+1, deg+n+1) == 0) {
            printf("-1\n");
            continue;
        }
        vector< pair<int,int> > res;
        while (!all.empty()) {
            int u = all.begin()->second;
            int v = all.rbegin()->second;

            all.erase(make_pair(deg[u], u));
            all.erase(make_pair(deg[v], v));
            --deg[u];
            --deg[v];
            res.push_back(make_pair(u, v));

            if (deg[u]) all.insert(make_pair(deg[u], u));
            if (deg[v]) all.insert(make_pair(deg[v], v));
        }
        for(auto p : res) printf("%d %d\n", p.first, p.second);
    }
}
