
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

double a[100111], f[100111];
int n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        double sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i];
        }
        FORD(i,n,1) {
            if (i == n) {
                f[n] = a[n];
            }
            else {
                sum += 2 * a[i] * f[i+1];
                f[i] = a[i] * f[i+1] + a[i];
            }
        }
        cout << (fixed) << setprecision(9) << sum << endl;
    }
}
