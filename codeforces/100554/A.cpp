
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, m, a[55], b[55];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> m;
        --n;
        int suma = 0, sumb = 0;
        FOR(i,1,n) {
            cin >> a[i];
            suma += a[i];
        }
        FOR(i,1,m) {
            cin >> b[i];
            sumb += b[i];
        }

        int nn = 100, ln = 0;
        FOR(x,0,100) {
            if (sumb < x*m && x*n < suma) {
                nn = min(nn, x);
                ln = max(ln, x);
            }
        }
        cout << nn << ' ' << ln << endl;
    }
}
