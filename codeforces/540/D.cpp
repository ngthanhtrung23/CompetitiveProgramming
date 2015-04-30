
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

double f[111][111][111];

int main() {
    ios :: sync_with_stdio(false);
    int x, y, z;
    while (cin >> x >> y >> z) {
        memset(f, 0, sizeof f);
        f[x][y][z] = 1.0;

        FORD(a,x,0) FORD(b,y,0) FORD(c,z,0)
            if (f[a][b][c] > 1e-150) {
                int sum = a + b + c;
                int all = sum * (sum - 1) / 2;
                all -= a * (a - 1) / 2;
                all -= b * (b - 1) / 2;
                all -= c * (c - 1) / 2;

                // a + b --> a
                if (a && b) f[a][b-1][c] += f[a][b][c] * (a * b)  / all;
                
                // b + c --> b
                if (b && c) f[a][b][c-1] += f[a][b][c] * (b * c)  / all;

                // c + a --> c
                if (c && a) f[a-1][b][c] += f[a][b][c] * (c * a)  / all;
            }

        double aa = 0, bb = 0, cc = 0;
        FOR(a,0,x) FOR(b,0,y) FOR(c,0,z) {
            if (a == 0 && b == 0) cc += f[a][b][c];
            if (a == 0 && c == 0) bb += f[a][b][c];
            if (b == 0 && c == 0) aa += f[a][b][c];
        }
        cout << (fixed) << setprecision(12) << aa << ' ' << bb << ' ' << cc << endl;
    }
    return 0;
}
