
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

const int MN = 5011;
pair<int,int> row[MN];
pair<int,int> col[MN];
int m, n, q;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d%d", &m, &n, &q) == 3) {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        FOR(i,1,q) {
            int typ; scanf("%d", &typ);
            int u, val;
            scanf("%d%d", &u, &val);

            if (typ == 1) {
                row[u] = make_pair(i, val);
            }
            else {
                col[u] = make_pair(i, val);
            }
        }
        FOR(i,1,m) {
            FOR(j,1,n) {
                auto t = max(row[i], col[j]);
                printf("%d ", t.second);
            }
            puts("");
        }
    }
}
