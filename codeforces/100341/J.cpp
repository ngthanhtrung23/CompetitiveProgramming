
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
#define double long double
using namespace std;

const int MN = 311;
const ll INF = 1e15;
pair<ll,int> c[MN][MN];
int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
    int m;
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        FOR(i,1,n) FOR(j,1,n) {
            c[i][j] = (i == j) ? make_pair(0LL, 0) : make_pair(INF, 0);
        }

        FOR(i,1,m) {
            int u, v; ll cost; cin >> u >> v >> cost;
            c[u][v] = min(c[u][v], make_pair(cost, 1));
            c[v][u] = c[u][v];
        }
        FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) {
            pair<ll,int> cur = make_pair(
                    c[i][k].first + c[k][j].first,
                    c[i][k].second + c[k][j].second);
            if (cur < c[i][j]) {
                c[i][j] = cur;
            }
        }
        double sum = 0;
        double cnt = 0;
        FOR(i,1,n) FOR(j,i+1,n) {
            cnt += 1;
            sum += c[i][j].second;
        }
        cout << sum / cnt << endl;
    }
}
