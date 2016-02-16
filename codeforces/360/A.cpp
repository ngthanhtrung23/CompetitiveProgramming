
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
int n, m;
int a[MN], add[MN], save[MN];
struct Query {
    int typ, l, r, x;
} q[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m) {
        FOR(i,1,n) a[i] = 1e9;
        memset(add, 0, sizeof add);
        FOR(i,1,m) {
            cin >> q[i].typ >> q[i].l >> q[i].r >> q[i].x;
            if (q[i].typ == 1) {
                FOR(x,q[i].l,q[i].r) add[x] += q[i].x;
            }
            else {
                FOR(x,q[i].l,q[i].r) a[x] = min(a[x], q[i].x - add[x]);
            }
        }

        FOR(i,1,n) save[i] = a[i];
        bool ok = true;
        FOR(i,1,m) {
            if (q[i].typ == 1) {
                FOR(x,q[i].l,q[i].r) a[x] += q[i].x;
            }
            else {
                int ln = a[q[i].l];
                FOR(x,q[i].l,q[i].r) ln = max(ln, a[x]);
                if (ln != q[i].x) {
                    ok = false;
                    break;
                }
            }
        }
        FOR(i,1,n) a[i] = save[i];

        if (!ok) {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;
        FOR(i,1,n) cout << a[i] << ' '; cout << endl;
    }
}
