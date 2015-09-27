
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

const int MN = 100111;
int n, m, a[MN];
ll f[MN][2][2][2];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        string s;
        cin >> s;
        FOR(i,1,n) a[i] = s[i-1] - 'a';

//        PR(a, n);
        a[n+1] = a[n+2] = -1;

        memset(f, 0, sizeof f);
        REP(add,m) {
            int x = 1; // b[1..1] - a[1..0]
            int y = (add == a[1]); // b[1..1] - a[1..1]
            int z = (add == a[1]) || (add == a[2]); // b[1..1] - a[1..2]
            f[1][x][y][z] += 1;
        }

        FOR(i,1,n-1) REP(x,2) REP(y,2) REP(z,2)
            REP(add,m) {
                int xx, yy, zz;
                // lcs[i+1][i]
                if (add == a[i]) xx = x;
                else xx = y;
                // lcs[i+1][i+1]
                if (add == a[i+1]) yy = y;
                else yy = max(xx, z) - 1;
                if (yy < 0) continue;
                // lcs[i+1][i+2]
                if (add == a[i+2]) zz = z;
                else zz = yy;

                f[i+1][xx][yy][zz] += f[i][x][y][z];
            }

        ll res = 0;
        REP(x,2) REP(z,2)
            res += f[n][x][0][z];
        cout << res << endl;
    }
}

