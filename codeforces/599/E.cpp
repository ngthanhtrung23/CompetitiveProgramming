
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 13;
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int edge[MN][MN], lca[MN][MN];
ll f[MN][1<<MN];
int n, m, q;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m >> q) {
        memset(edge, 0, sizeof edge);
        memset(lca, -1, sizeof lca);
        bool ok = true;
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            --u; --v;
            edge[u][v] = edge[v][u] = 1;
            if (u == v) {
                ok = false;
            }
        }
        FOR(i,1,q) {
            int u, v, l; cin >> u >> v >> l;
            --u; --v; --l;
            if (lca[u][v] >= 0 && lca[u][v] != l) {
                ok = false;
            }
            if (u == v && l != u) {
                ok = false;
            }
            lca[u][v] = lca[v][u] = l;
        }
        if (!ok) {
            cout << 0 << endl;
            continue;
        }
        memset(f, 0, sizeof f);
        REP(mask,TWO(n)) REP(x, n) {
            if (CONTAIN(mask,x)) {
                // how many trees with root x & contains nodes in mask
                if (__builtin_popcount(mask) == 1) {
                    // only 1 node in this tree
                    f[x][mask] = 1;
                }
                else {
                    // x has only 1 child
                    REP(y,n) if (CONTAIN(mask,y) && y != x) {
                        bool can = true;
                        // check edge conditions
                        // only need to check edges (x - i)
                        REP(i,n) if (i != x && i != y && CONTAIN(mask, i) && edge[x][i]) {
                            can = false;
                            break;
                        }
                        // check lca conditions
                        // only need to check lca(x, i) = x
                        REP(i,n) if (i != x && CONTAIN(mask, i) && lca[x][i] >= 0 && lca[x][i] != x) {
                            can = false;
                            break;
                        }
                        if (can) f[x][mask] += f[y][mask - TWO(x)];
                    }
//                    if (x == 0 && mask == 15) {
//                        DEBUG(f[x][mask]);
//                    }
                    // x has many child
                    // we will split (mask - {x}) into S1 and S2
                    // to avoid double counting, need to make sure the smallest bit in mask is also in S1 (force order of merging trees)

                    int mask_x = mask - TWO(x);
                    int leastChild = mask_x & (-mask_x);
                    for(int s1 = mask; s1 > 0; s1 = (mask & (s1 - 1))) if (CONTAIN(s1, x) && __builtin_popcount(s1) > 1) {
                        int s2 = mask - s1;
                        if (s2 == 0) continue;
                        if (!(s2 & leastChild)) continue;

                        REP(y,n) if (CONTAIN(s2,y)) {
                            bool can = true;
                            
                            // check edge conditions, lca conditions
                            // (u, v) where u in s1, v in s2
                            REP(u,n) if (CONTAIN(s1, u))
                                REP(v,n) if (CONTAIN(s2,v)) {
                                    // edge conditions
                                    if (edge[u][v] && !(u == x && y == v)) {
                                        can = false;
                                        break;
                                    }
                                    // lca conditions
                                    if (lca[u][v] >= 0 && lca[u][v] != x) {
                                        can = false;
                                        break;
                                    }
                                }

                            if (can) {
                                f[x][mask] += f[x][s1] * f[y][s2];
                            }
                        }
                    }

//                    if (x == 0 && mask == 15) {
//                        DEBUG(f[x][mask]);
//                    }
                }
            }
        }
//        REP(x,n) {
//            PR0(f[x], TWO(n));
//        }
        cout << f[0][TWO(n) - 1] << endl;
    }
}
