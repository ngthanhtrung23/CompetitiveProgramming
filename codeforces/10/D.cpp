
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

const int MN = 511;
int f[MN][MN], x[MN], savej[MN];
int tri[MN][MN], trj[MN][MN];
int na, nb, a[MN], b[MN];

void trace(int i, int j) {
    if (!i) return ;

    assert(a[i] == b[j]);

    trace(tri[i][j], trj[i][j]);
    cout << a[i] << ' ';
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> na) {
        FOR(i,1,na) cin >> a[i];

        cin >> nb;
        FOR(i,1,nb) cin >> b[i];

        FOR(i,1,na) FOR(j,1,nb) if (a[i] != b[j]) f[i][j] = -MN; else f[i][j] = 1;
        memset(tri, 0, sizeof tri);
        memset(trj, 0, sizeof trj);

        int res = 0;
        FOR(i,1,na) {
            FOR(u,1,i-1) x[u] = -MN;

            FOR(j,1,nb) {
                FOR(u,1,i-1) {
                    int cur = f[u][j-1];
                    if (cur > x[u]) {
                        x[u] = cur;
                        savej[u] = j-1;
                    }
                }
                if (a[i] != b[j]) continue;

                FOR(u,1,i-1) if (a[u] < a[i]) {
                    int cur = x[u] + 1;
                    if (cur > f[i][j]) {
                        f[i][j] = cur;
                        tri[i][j] = u;
                        trj[i][j] = savej[u];
                    }
                }
                res = max(res, f[i][j]);
            }
        }
        cout << res << endl;
        FOR(i,1,na) FOR(j,1,nb) if (f[i][j] == res) {
            trace(i, j);
            goto done;
        }
done:
        cout << endl;
    }
}
