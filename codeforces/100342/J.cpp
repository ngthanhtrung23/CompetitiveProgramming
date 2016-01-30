
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

const int MN = 1511;

bitset<MN> ra[MN], vao[MN];
int c[MN][MN];
char tmp[MN];
int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("triatrip.in", "r", stdin);
    freopen("triatrip.out", "w", stdout);
    while (scanf("%d\n", &n) == 1) {
        memset(c, 0, sizeof c);
        FOR(i,1,n) {
            ra[i].reset();
            vao[i].reset();
        }
        FOR(i,1,n) {
            scanf("%s\n", &tmp[1]);
            FOR(j,1,n) {
                if (tmp[j] == '+') {
                    c[i][j] = 1;
                    ra[i][j] = 1;
                    vao[j][i] = 1;
                }
            }
        }
        ll res = 0;
        FOR(i,1,n) FOR(j,1,n) if (c[i][j]) {
            res += (ra[j] & vao[i]).count();
        }
        cout << res / 3 << endl;
    }
}
