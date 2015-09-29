
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

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; string typ; cin >> n >> typ;
        double res = 0.0;
        FOR(i,1,n) {
            double a;
            cin >> a;
            a /= 100.0;

            if (a > 0.001) {
                if (typ == "bit") res -= a * log(a) / log(2);
                else if (typ == "nat") res -= a * log(a);
                else res -= a * log(a) / log(10);
            }
        }
        cout << (fixed) << setprecision(9) << res << endl;
    }
}
