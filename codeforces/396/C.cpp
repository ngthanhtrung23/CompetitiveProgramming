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

const int MN = 300111;
const long long MOD = 1000000007;
int n, getIn[MN], getOut[MN], cur;
vector<int> ke[MN];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
#define MID ((l + r) >> 1)
struct IT {
    long long x[MN * 4];
    void init() { memset(x, 0, sizeof x); }

    void update(int i, int l, int r, int u, int v, long long val) {
        if (v < l || r < u) return ;
        if (u <= l && r <= v) {
            x[i] = (x[i] + val) % MOD;
            return ;
        }
        update(CT(i), l, MID, u, v, val);
        update(CP(i), MID+1, r, u, v, val);
    }

    long long get(int i, int l, int r, int u) {
        if (u < l || r < u) return 0;
        if (l == r) return x[i];
        return (x[i] + get(CT(i), l, MID, u) + get(CP(i), MID+1, r, u)) % MOD;
    }
} it1, it2;

int level[MN];

void dfs(int u) {
    getIn[u] = ++cur;
    for(auto v : ke[u]) {
        level[v] = level[u] + 1;
        dfs(v);
    }
    getOut[u] = cur;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        level[1] = 1;
        FOR(i,2,n) {
            int pi; cin >> pi;
            ke[pi].push_back(i);
        }
        it1.init();
        it2.init();

        dfs(1);

        int q; cin >> q;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u, x, k; cin >> u >> x >> k;
                it1.update(1, 1, n, getIn[u], getOut[u], (x + k * (long long) level[u]) % MOD);
                it2.update(1, 1, n, getIn[u], getOut[u], k);
            }
            else {
                int u; cin >> u;
                cout << ((it1.get(1, 1, n, getIn[u]) - it2.get(1, 1, n, getIn[u]) * level[u]) % MOD + MOD) % MOD << "\n";
            }
        }
    }
    return 0;
}

