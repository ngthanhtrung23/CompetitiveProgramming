
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

const int MN = 3011;
const int MOD = 1e9 + 7;

char a[MN][MN];
ll f[MN][MN];
int m, n;

ll cal(pair<int,int> from, pair<int,int> to) {
    int u1 = from.first, v1 = from.second;
    int u2 = to.first, v2 = to.second;

    memset(f, 0, sizeof f);
    FOR(i,u1,u2) FOR(j,v1,v2) {
        if (a[i][j] == '#') {
            f[i][j] = 0;
        }
        else if (i == u1 && j == v1) {
            f[i][j] = 1;
        }
        else {
            f[i][j] = (f[i-1][j] + f[i][j-1]) % MOD;
        }
    }
    return f[u2][v2];
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        pair<int,int> a1 = make_pair(1, 2);
        pair<int,int> a2 = make_pair(2, 1);
        pair<int,int> b1 = make_pair(m-1, n);
        pair<int,int> b2 = make_pair(m, n-1);

        ll res = (cal(a1, b1) * cal(a2, b2)
                - cal(a2, b1) * cal(a1, b2)) % MOD;
        if (res < 0) res += MOD;
        cout << res << endl;
    }
}
