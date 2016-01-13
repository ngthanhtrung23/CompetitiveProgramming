
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

const int MN = 111;
int a[MN];
ll f[MN];
bool used[MN];
int deg[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        memset(used, 0, sizeof used);
        memset(deg, 0, sizeof deg);

        while (m--) {
            int u, v; cin >> u >> v;
            ++deg[u];
        }

        REP(i,n) {
            int cnt_lower = deg[i];

            a[i] = -1;
            REP(turn,cnt_lower+1) {
                ++a[i];
                while (used[a[i]]) ++a[i];
            }
            used[a[i]] = 1;
        }
//        PR0(a, n);

        ll res = 0;
        REP(i,n) {
            bool ok = 1;
            REP(j,i) if (a[j] < a[i]) ok = 0;
            f[i] = ok;

            int x = -1;
            FORD(j,i-1,0) if (a[j] < a[i]) {
                if (a[j] < x) continue;
                x = max(x, a[j]);

                f[i] += f[j];
            }

            ok = 1;
            FOR(j,i+1,n-1) if (a[j] > a[i]) ok = 0;
            res += f[i] * ok;
        }
//        PR0(f, n);
        cout << res << endl;
    }
}
