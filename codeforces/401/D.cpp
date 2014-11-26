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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
string s;
int n, m;
long long f[TWO(18)][111];
bool ok[TWO(18)];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s >> m) {
        n = s.length();
        memset(f, 0, sizeof f);
        memset(ok, true, sizeof ok);
        f[0][0] = 1;
        REP(mask,TWO(n)) {
            REP(i,n) if (CONTAIN(mask,i))
                REP(j,n) if (!CONTAIN(mask,j))
                    if (s[i] == s[j] && i > j)
                        ok[mask] = false;
        }
        REP(mask,TWO(n)-1) REP(rem,m) if (f[mask][rem]) {
            REP(next,n)
                if (!CONTAIN(mask,next))
                if (mask || s[next] > '0') {
                    if (ok[mask | TWO(next)])
                        f[mask | TWO(next)][(rem*10 + s[next] - '0') % m] += f[mask][rem];
                }
        }
        cout << f[TWO(n)-1][0] << endl;
    }
    return 0;
}
