
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, m, k;
int ke[12][12], concert[12][12];
double f[TWO(10) + 12];
int tr[TWO(10) + 12];
int ordinary[12], crazy[12], maniac[12], info[12];

void trace(int s) {
    if (s == 0) return ;
    trace(s - TWO(tr[s]));
    cout << tr[s]+1 << ' ';
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("musical.in", "r", stdin);
    freopen("musical.out", "w", stdout);
    while (cin >> n >> m >> k) {
        REP(i,n) cin >> ordinary[i] >> crazy[i] >> maniac[i];
        memset(ke, 0, sizeof ke);
        REP(i,m) {
            int u, v; cin >> u >> v;
            --u; --v;
            ke[u][v] = ke[v][u] = 1;
        }
        memset(concert, 0, sizeof concert);
        REP(i,k) {
            REP(j,n) {
                int x; cin >> x; --x;
                concert[i][j] = x;
            }
        }
        memset(f, 0, sizeof f);
        REP(s,TWO(n) - 1) {
            REP(i,n) if (!CONTAIN(s,i)) {
                int s2 = s + TWO(i);
                double cur = f[s];

                int week = __builtin_popcount(s); // we already passed this number of week

                // ordinary fans --> calculate info[c] = neighbors[i] that has concert c
                memset(info, 0, sizeof info);
                REP(c,k) {
                    if (concert[c][week] != i) {
                        info[c] = -1;  // ordinary fans can't go to this concert (diff city)
                        continue;
                    }
                    int neighbor = 0;
                    REP(w,week) {
                        int u = concert[c][w];
                        if (ke[u][i])
                            neighbor |= TWO(u);
                    }
                    info[c] = __builtin_popcount(neighbor);
                }
                // info[k] = neighbors[i] that has our concert
                REP(u,n) if (CONTAIN(s,u) && ke[u][i]) ++info[k];

                int best_info = *max_element(info, info+k+1);
                if (info[k] == best_info) {
                    int cnt_best = 0;
                    FOR(c,0,k) if (info[c] == best_info) ++cnt_best;

                    cur += ordinary[i] / (double) cnt_best;
                }

                // crazy fans
                int cnt = 0;
                REP(c,k) if (concert[c][week] == i) ++cnt;
                cur += crazy[i] /(double) (cnt + 1) * 7.0;

                // maniac fans
                REP(u,n) if (u == i || ke[u][i]) {
                    // consider the maniac fans in city u
                    // how many concerts can a maniac fan go to
                    int cnt = 1;
                    REP(c,k) {
                        int v = concert[c][week];
                        if (v == u || ke[u][v]) ++cnt;
                    }
                    cur += maniac[u] * 7 / (double) (cnt);
                }

                if (cur > f[s2]) {
                    f[s2] = cur;
                    tr[s2] = i;
                }
            }
        }
        cout << (fixed) << setprecision(9) << f[TWO(n) - 1] << endl;
        trace(TWO(n) - 1); cout << endl;
    }
}
