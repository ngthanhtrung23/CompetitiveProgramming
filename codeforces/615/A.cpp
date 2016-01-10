
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
int n, m;
int can[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m) {
        memset(can, 0, sizeof can);
        FOR(i,1,n) {
            int k; cin >> k;
            while (k--) {
                int u; cin >> u;
                can[u] = true;
            }
        }
        bool all = true;
        FOR(i,1,m) if (!can[i]) all = false;
        cout << (all ? "YES" : "NO") << endl;
    }
}
