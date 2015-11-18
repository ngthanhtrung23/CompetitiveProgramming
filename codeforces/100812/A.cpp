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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 1011;

ll val[MN];
ll a[MN][MN], res[MN][MN];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    int n;
    while (scanf("%d", &n) == 1) {
        memset(val, 0, sizeof val);
        FOR(i,1,n) FOR(j,1,n) {
            int x; scanf("%d", &x);
            a[i][j] = x;

            val[i] -= x;
            val[j] += x;
        }
        memset(res, 0, sizeof res);
        set<int> pos, neg;
        FOR(i,1,n) {
            if (val[i] < 0) neg.insert(i);
            if (val[i] > 0) pos.insert(i);
        }
        while (!pos.empty()) {
            int u = *pos.begin(); pos.erase(pos.begin());
            int v = *neg.begin(); neg.erase(neg.begin());

            ll can = min(val[u], -val[v]);
            res[v][u] = can;
            val[v] += can;
            val[u] -= can;

            if (val[u] > 0) pos.insert(u);
            if (val[v] < 0) neg.insert(v);
        }
        FOR(i,1,n) {
            FOR(j,1,n) printf("%lld ", res[i][j]);
            puts("");
        }
    }
}
