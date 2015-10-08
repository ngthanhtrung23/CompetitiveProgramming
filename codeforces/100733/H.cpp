
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

int c[33][33], cost[33][33];
string s;

int main() {
    ios :: sync_with_stdio(false);
    REP(i,26) REP(j,26) cin >> c[i][j];
    REP(i,26) c[i][i] = 0;
    REP(k,26) REP(i,26) REP(j,26) c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

    REP(i,26) REP(j,26) {
        if (i == j) cost[i][j] = 0;
        else {
            cost[i][j] = 1000111000;
            REP(k,26) cost[i][j] = min(cost[i][j], c[i][k] + c[j][k]);
        }
    }

    cin >> s;
    ll res = 0;
    for(int i = 0, j = s.length() - 1; i < j; ++i, --j)
        res += cost[s[i] - 'a'][s[j] - 'a'];
    cout << res << endl;
}
