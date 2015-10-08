
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

int n, v[1000111], f[1000111];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &v[i]);
        FOR(i,1,n) {
            if (i < 3) f[i] = max(f[i-1], v[i]);
            else f[i] = max(f[i-1], v[i] + f[i-3]);
        }
        cout << f[n] << endl;
    }
}
