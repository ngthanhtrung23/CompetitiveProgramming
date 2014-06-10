#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;
const int oo = 1000111000;

int n, m, s, e;
int f[411][MN];
vector<int> b[MN];
int a[MN];

#define update(turn, a, b) if (turn*(long long) e + a + b <= s) res = max(res, turn);

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> s >> e) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,100000) b[i].clear();
        FOR(i,1,m) {
            int x; cin >> x;
            b[x].push_back(i);
        }
        int res = 0;

        f[0][0] = 0;
        FOR(turn,1,s/e) {
            FOR(i,0,n) f[turn][i] = oo;
            FOR(i,1,n) {
                if (b[a[i]].empty()) {
                    f[turn][i] = oo;
                }
                else {
                    int u = a[i];
                    if (b[u][b[u].size()-1] <= f[turn-1][i-1]) {
                        f[turn][i] = oo;
                        continue;
                    }
                    f[turn][i] = *upper_bound(b[u].begin(), b[u].end(), f[turn-1][i-1]);

                    update(turn, i, f[turn][i]);
                }
            }

            FOR(i,2,n) {
                f[turn][i] = min(f[turn][i], f[turn][i-1]);
                update(turn, i, f[turn][i]);
            }
        }

        cout << res << endl;
    }
    return 0;
}
