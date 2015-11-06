
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

#define y0 y0__
int x0, y0, n, d;
int f[411][411][2][2][2];
int x[22], y[22];

int get(int x0, int y0, int turn, int c0, int c1) {
    if (f[x0 + 200][y0 + 200][turn][c0][c1] >= 0)
        return f[x0 + 200][y0 + 200][turn][c0][c1];

    int& res = f[x0 + 200][y0 + 200][turn][c0][c1];

    if (turn == 0) {
        // reflect
        if (c0 == 0) {
            if (get(y0, x0, 1-turn, 1, c1) == 0)
                return res = 0;
        }
        // translate using a vector
        FOR(i,1,n) {
            if (sqr(x0 + x[i]) + sqr(y0 + y[i]) <= d*d)
            if (get(x0 + x[i], y0 + y[i], 1-turn, c0, c1) == 0)
                return res = 0;
        }
        return res = 1;
    }
    else {
        // reflect
        if (c1 == 0) {
            if (get(y0, x0, 1-turn, c0, 1) == 1)
                return res = 1;
        }
        // translate
        FOR(i,1,n) {
            if (sqr(x0 + x[i]) + sqr(y0 + y[i]) <= d*d)
            if (get(x0 + x[i], y0 + y[i], 1-turn, c0, c1) == 1)
                return res = 1;
        }
        return res = 0;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> x0 >> y0 >> n >> d) {
        memset(f, -1, sizeof f);
        FOR(i,1,n) cin >> x[i] >> y[i];
        cout << (get(x0, y0, 0, 0, 0) == 0 ? "Anton" : "Dasha") << endl;
    }
}
