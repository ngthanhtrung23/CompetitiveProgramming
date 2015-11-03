
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

#define __ 22][22][22][2][2][2
#define STATE ii][jj][kk][newRem][newEndx][newEndy

int f[__];
int tri[__];
int trj[__];
int trk[__];
int trr[__];
int trEndx[__];
int trEndy[__];
int trX[__];
int trY[__];
int trZ[__];

#define CUR i][j][k][rem][endx][endy
void trace(int i, int j, int k, int rem, int endx, int endy, string& x, string& y, string& z) {
    if (i == 0 && j == 0 && k == 0 && rem == 0 && endx == 0 && endy == 0) {
        return ;
    }

    x += (char) ('0' + trX[CUR]);
    y += (char) ('0' + trY[CUR]);
    z += (char) ('0' + trZ[CUR]);

    trace(tri[CUR], trj[CUR], trk[CUR],
            trr[CUR], trEndx[CUR], trEndy[CUR],
            x, y, z);
}

int main() {
    ios :: sync_with_stdio(false);
    string s;
    while (cin >> s) {
        REP(i,SZ(s)) if (s[i] == '+' || s[i] == '=') s[i] = ' ';
        stringstream ss(s);
        string a, b, c;
        ss >> a >> b >> c;

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        reverse(c.begin(), c.end());

        int la = SZ(a); a = " " + a;
        int lb = SZ(b); b = " " + b;
        int lc = SZ(c); c = " " + c;

        memset(f, 0x3f, sizeof f);
        f[0][0][0][0][0][0] = 0;

        FOR(i,0,la) FOR(j,0,lb) FOR(k,0,lc) REP(rem,2) REP(endx,2) REP(endy,2) {
            int cur = f[i][j][k][rem][endx][endy];
            if (cur > 100) continue;
            REP(x,10) REP(y,10) {
                if (endx && x) continue;
                if (endy && y) continue;

                int ii = i; if (!endx && ii < la && x == a[ii+1] - '0') ++ii;
                int jj = j; if (!endy && jj < lb && y == b[jj+1] - '0') ++jj;

                int z = (x + y + rem) % 10;
                int newRem = (x + y + rem) / 10;

                int kk = k; if (kk < lc && z == c[kk+1] - '0') ++kk;

                int next = cur + 1;
                if (!endx) ++next;
                if (!endy) ++next;

                FOR(newEndx,endx,1) if (x || newEndx == endx)
                    FOR(newEndy,endy,1) if (y || newEndy == endy)
                        if (f[STATE] > next) {
                            f[STATE] = next;
                            tri[STATE] = i;
                            trj[STATE] = j;
                            trk[STATE] = k;
                            trr[STATE] = rem;
                            trEndx[STATE] = endx;
                            trEndy[STATE] = endy;
                            trX[STATE] = x;
                            trY[STATE] = y;
                            trZ[STATE] = z;
                        }
            }
        }
        string x = "";
        string y = "";
        string z = "";
        trace(la, lb, lc, 0, 1, 1, x, y, z);
        while (SZ(x) > 1 && x[0] == '0') x = x.substr(1);
        while (SZ(y) > 1 && y[0] == '0') y = y.substr(1);
        while (SZ(z) > 1 && z[0] == '0') z = z.substr(1);
        cout << x << '+' << y << '=' << z << endl;
    }
}
