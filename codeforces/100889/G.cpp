
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

int l[77], r[77], a[77], b[77];
int f[77][2][2][2][2];

void update(int& x, int val) {
    x = max(x, val);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    while (ntest--) {
        int L, R, A, B;
        GI(L); GI(R); GI(A); GI(B);

        FOR(i,1,60) {
            int t = 60 - i;
            l[i] = (L >> t) & 1;
            r[i] = (R >> t) & 1;
            a[i] = (A >> t) & 1;
            b[i] = (B >> t) & 1;
        }
        memset(f, -1, sizeof f);
        f[0] [0][0][0][0] = 0;
        FOR(i,0,59) REP(gl,2) REP(lr,2) REP(la,2) REP(lb,2) {
            int val = f[i][gl][lr][la][lb];
            if (val < 0) continue;

            REP(curx,2)
            if (gl || curx >= l[i+1])
            if (lr || curx <= r[i+1])
                REP(cury,2)
                if (la || cury <= a[i+1])
                    REP(curz,2)
                    if (lb || curz <= b[i+1]) {
                        int gl2 = gl; if (curx > l[i+1]) gl2 = 1;
                        int lr2 = lr; if (curx < r[i+1]) lr2 = 1;
                        int la2 = la; if (cury < a[i+1]) la2 = 1;
                        int lb2 = lb; if (curz < b[i+1]) lb2 = 1;

                        int t = val;

                        update(f[i+1][gl2][lr2][la2][lb2],
                                val + ((curx ^ cury) << (60 - i - 1))
                                    + ((cury & curz) << (60 - i - 1))
                                    + ((curz ^ curx) << (60 - i - 1)));
                    }
        }
        int res = -1;
        REP(x,2) REP(y,2) REP(z,2) REP(t,2)
            res = max(res, f[60][x][y][z][t]);
        printf("%lld\n", res);
    }
}
