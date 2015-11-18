
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

const int MN = 1011;

int n;
ll d, t[MN], c, sumt[MN], f[MN];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    while (cin >> n >> d >> c) {
        FOR(i,1,n) {
            cin >> t[i];
            sumt[i] = sumt[i-1] + t[i];
        }
        f[0] = 0;
        FOR(i,1,n) {
            f[i] = f[i-1] + d;
            FOR(j,0,i-1) {
                ll delay = t[i] * (i - j) - (sumt[i] - sumt[j]);
                f[i] = min(f[i], d + delay * c + f[j]);
            }
        }
        cout << f[n] << endl;
    }
}
