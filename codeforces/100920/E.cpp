
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO (X))

int eu[44], ev[44];
int n, m;
int f[(1<<20) + 11];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m) {
        FOR(i,1,m) {
            cin >> eu[i] >> ev[i];
            --eu[i]; --ev[i];
        }
        REP(i,TWO(n)) f[i] = 1000111;

        f[0] = 0;
        REP(s,TWO(n) - 1) {
            FOR(i,1,m) {
                int s2 = s | TWO(eu[i]) | TWO(ev[i]);
                f[s2] = min(f[s2], f[s] + 1);
            }
        }
        int res = m; // all edges blue
        REP(s,TWO(n)) {
            int cur = f[s];
            int cnt = 0;
            FOR(i,1,m) {
                if (CONTAIN(s,eu[i]) || CONTAIN(s,ev[i])) ++cnt;
            }
            int cost = cur * 2 + (m - cnt);
            res = min(res, cost);
        }
        cout << res << endl;
    }
}
