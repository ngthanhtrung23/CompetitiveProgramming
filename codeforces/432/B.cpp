#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int x[MN], y[MN], cntx[MN], cnty[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n) {
        memset(cntx, 0, sizeof cntx);
        memset(cnty, 0, sizeof cnty);
        FOR(i,1,n) {
            cin >> x[i] >> y[i];
            cntx[x[i]] += 1;
            cnty[y[i]] += 1;
        }

        FOR(i,1,n) {
            int a = n-1, b = n-1;
            a += cntx[y[i]];
            b -= cntx[y[i]];

            cout << a << ' ' << b << "\n";
        }
    }
    return 0;
}
