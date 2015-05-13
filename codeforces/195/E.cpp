
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
const int MOD = 1e9 + 7;
int n;
int father[MN], sum[MN];

pair<int,int> get(int u) {
    if (father[u] < 0) return make_pair(u, 0);

    auto cur = get(father[u]);
    father[u] = cur.first;
    sum[u] = (sum[u] + cur.second) % MOD;

    return make_pair(father[u], sum[u]);
}

void link(int u, int v, int cost) {
    father[u] = v;
    sum[u] = cost;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int res = 0;
        memset(father, -1, sizeof father);

        FOR(i,1,n) {
            int k; cin >> k;
            while (k--) {
                int u, x; cin >> u >> x;
                x = (x + MOD) % MOD;
                pair<int,int> cur = get(u);

                cur.second = (cur.second + x) % MOD;
                link(cur.first, i, cur.second);

                res = (res + cur.second) % MOD;
            }
        }
        cout << res << endl;
    }
    return 0;
}
