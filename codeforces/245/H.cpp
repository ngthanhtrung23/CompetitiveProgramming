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

const int MN = 5011;
string s;
int f[MN][MN];

int main() {
    while (cin >> s) {
        int n = s.length();
        s = " " + s;
        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) f[i][i] = 1;
            else if (i+1 == j) f[i][j] = s[i] == s[j];
            else f[i][j] = (s[i] == s[j]) && f[i+1][j-1];
        }
        FORD(i,n,1) FOR(j,i+1,n) {
            f[i][j] = f[i][j-1] + f[i+1][j] - f[i+1][j-1] + f[i][j];
        }
        int q; scanf("%d\n", &q);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            printf("%d\n", f[u][v]);
        }
    }
    return 0;
}

