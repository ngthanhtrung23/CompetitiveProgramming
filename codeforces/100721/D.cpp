
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

struct Cup {
    int h, r, R;
} a[11];

double c[11][11], h[11];
int x[11];

double getRelative(Cup a, Cup b) {
    double alpha_a = a.h / (double) (a.R - a.r);
    double alpha_b = b.h / (double) (b.R - b.r);

    if (a.r >= b.R) return b.h;

    if (alpha_b > alpha_a) {
        if (a.R >= b.R && b.R > a.r) return max(0.0, b.h - (b.R - a.r) * alpha_a);
        return max(0.0, (a.R - b.r) * alpha_b - a.h);
    }
    else {
        double res = (a.r - b.r) * alpha_b;
        res = min(res, (double) b.h);
        res = max(res, 0.0);
        return res;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        FOR(i,1,n) cin >> a[i].h >> a[i].r >> a[i].R;

        FOR(i,1,n) FOR(j,1,n) if (i != j) {
            c[i][j] = getRelative(a[i], a[j]);
            c[i][j] = max(c[i][j], 0.0);
            c[i][j] = min(c[i][j], (double) a[j].h);
        }

        FOR(i,1,n) x[i] = i;
        double res = 1e100;
        do {
            FOR(turn,1,n) {
                int u = x[turn];
                h[turn] = 0.0;

                FOR(i,1,turn-1) h[turn] = max(h[turn], h[i] + c[u][x[i]]);
            }
            double cur = 0.0;
            FOR(i,1,n) cur = max(cur, h[i] + a[x[i]].h);

            res = min(res, cur);
            if (n == 3 && cur < 9) {
                PR(x, n);
                DEBUG(cur);
            }
        } while (next_permutation(x+1, x+n+1));
        
        cout << (int) (res + 1e-6) << endl;
    }
}
