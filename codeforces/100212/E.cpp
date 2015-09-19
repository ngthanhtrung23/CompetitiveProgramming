#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

int p3[11];
long long f[33][10][20111];

inline int getBit(int s, int k) {
    return (s % p3[k+1]) / p3[k];
}

inline int setBit(int s, int k, int val) {
    return s + p3[k] * (val - getBit(s, k));
}

int main() {
    freopen("dominoes.in", "r", stdin);
    freopen("dominoes.out", "w", stdout);

    p3[0] = 1; FOR(i,1,9) p3[i] = p3[i-1] * 3;

    int m, n;
    while (cin >> n >> m) {
        if (n > m) swap(m, n);

        memset(f, 0, sizeof f);
        f[0][0][p3[n]-1] = 1;

        REP(i,m) REP(j,n) REP(mask,p3[n]) if (f[i][j][mask]) {
            // cout << i << ' ' << j << ' ' << mask << "   " << f[i][j][mask] << endl;
            int newMask = mask, x, y, z;

            int ii = i, jj = j + 1;
            if (jj == n) {
                ++ii;
                jj = 0;
            }

            // Keep (i, j) empty
            x = getBit(mask, j);
            if (x) {
                f[ii][jj][setBit(mask, j, x - 1)] += f[i][j][mask];
            }

            // Put vertical at (i, j)
            x = getBit(mask, j);
            if (x == 0) {
                f[ii][jj][setBit(mask, j, 2)] += f[i][j][mask];
            }

            // Put horizontal at (i, j)
            if (j >= 2) {
                z = getBit(mask, j-2);
                y = getBit(mask, j-1);
                x = getBit(mask, j);
                if (x == 2 && y == 1 && z == 1) {
                    newMask = mask;
                    newMask = setBit(newMask, j-2, 2);
                    newMask = setBit(newMask, j-1, 2);
                    newMask = setBit(newMask, j-0, 2);

                    f[ii][jj][newMask] += f[i][j][mask];
                }
            }
        }

        cout << f[m][0][p3[n] - 1] << endl;
    }
    return 0;
}