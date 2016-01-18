
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int it[MN * 4];
bool can[TWO(20)];
int x[MN];
int n, m, d;

void init(int i, int l, int r) {
    if (l == r) {
        it[i] = x[l];
        return ;
    }
    int mid = (l + r) >> 1;
    init(i<<1, l, mid);
    init(i<<1|1, mid+1, r);

    it[i] = it[i<<1] | it[i<<1|1];
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return get(i<<1, l, mid, u, v) | get(i<<1|1, mid+1, r, u, v);
}

int main() {
    while (scanf("%d%d%d", &n, &m, &d) == 3) {
        FOR(i,1,m) {
            int k; scanf("%d", &k);
            while (k--) {
                int u; scanf("%d", &u);
                x[u] = TWO(i - 1);
            }
        }
//        PR(x, n);

        init(1, 1, n);
        memset(can, 0, sizeof can);
        FOR(i,1,n-d+1) {
            int j = i + d - 1;
            int t = get(1, 1, n, i, j);
            can[t] = true;
        }

        REP(mask,TWO(m)) {
            if (can[mask]) continue;
            REP(i,m) if (CONTAIN(mask,i)) {
                can[mask] = can[mask] || can[mask - TWO(i)];
            }
        }
        int res = m + 1;
        REP(mask,TWO(m)) if (!can[mask]) res = min(res, m - __builtin_popcount(mask));

        cout << res << endl;
    }
}
