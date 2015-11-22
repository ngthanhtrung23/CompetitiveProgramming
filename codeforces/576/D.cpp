
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

const int MN = 155;

int n;
struct BMT {
    bitset<MN> x[MN];
} trans;

BMT operator * (const BMT& a, const BMT& b) {
    BMT res, b_trans;
    REP(i,n) REP(j,n) b_trans.x[i][j] = b.x[j][i];

    REP(i,n) REP(j,n) {
        res.x[i][j] = (a.x[i] & b_trans.x[j]).count() > 0;
    }
    return res;
}

BMT power(BMT a, int k) {
    BMT res;
    REP(i,n) {
        res.x[i].reset();
        res.x[i][i] = 1;
    }
    while (k > 0) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

struct Edge {
    int u, v, cost;

    void read() {
        cin >> u >> v >> cost;
        --u; --v;
    }
} edges[MN];
bool operator < (const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}
int nEdge;

#define next next__
bitset<MN> can, next;
int c[MN][MN];

const int INF = 1000111000;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> nEdge) {
        FOR(i,1,nEdge) edges[i].read();
        sort(edges+1, edges+nEdge+1);
        int cur_time = 0;

        REP(i,n) REP(j,n) trans.x[i][j] = 0;
        can.reset();
        can[0] = 1;

        int res = INF;
        FOR(i,1,nEdge) {
            // enable this edge
            int u = edges[i].u, v = edges[i].v;
            // update the current vector
            BMT go = power(trans, edges[i].cost - cur_time);
            REP(i,n) {
                next[i] = (go.x[i] & can).count() > 0;
            }
            can = next;
            cur_time = edges[i].cost;
//            cout << "Edge: " << u << ' ' << v << ' ' << edges[i].cost << endl;
//            PR0(can, n);

            // go from u --> v
            trans.x[v][u] = 1;


            // we fix the maximum number of edges here & do floyd
            REP(i,n) REP(j,n) c[i][j] = ((i == j) ? 0 : INF);
            REP(i,n) REP(j,n) {
                if (trans.x[i][j]) c[j][i] = 1;
            }
            REP(k,n) REP(i,n) REP(j,n)
                c[i][j] = min(c[i][k] + c[k][j], c[i][j]);

            REP(i,n) if (can.test(i))
                res = min(res, c[i][n-1] + cur_time);
        }
        if (res == INF) cout << "Impossible" << endl;
        else cout << res << endl;
    }
}

