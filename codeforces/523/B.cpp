
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 200111;
int n, T;
double c;
long long a[MN], s[MN];
double real_mean[MN], approx_mean[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> T >> c) {
        FOR(i,1,n) {
            cin >> a[i];
            s[i] = s[i-1] + a[i];
        }
        FOR(i,1,n) {
            if (i >= T) {
                real_mean[i] = (s[i] - s[i-T]) / (double) T;
            }
            approx_mean[i] = (approx_mean[i-1] + a[i] / (double) T) / c;
        }
        int q; cin >> q;
        while (q--) {
            int u; cin >> u;
            cout << real_mean[u] << ' ' << approx_mean[u] << ' ' << 
                fabs(real_mean[u] - approx_mean[u]) / real_mean[u] << '\n';
        }
    }
    return 0;
}
