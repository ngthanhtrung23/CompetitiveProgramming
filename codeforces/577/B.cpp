
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
using namespace std;

int n, m;
int a[1000111];
bool f[1011][1011];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
        }
        if (n >= m) {
            cout << "YES" << endl;
            continue;
        }
        memset(f, 0, sizeof f);
        FOR(i,1,n) {
            REP(old,m) if (f[i-1][old]) {
                f[i][old] = true;
                f[i][(old + a[i]) % m] = true;
            }
            f[i][ a[i] % m ] = true;
        }
        cout << (f[n][0] ? "YES" : "NO") << endl;
    }
}
