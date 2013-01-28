#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
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

const long double PI = acos((long double) -1.0);
const int MOD = 1000000009;

int n, h, f[2][33][33][33][33];

inline void update(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int next[33];

int main() {
    while (cin >> n >> h) {
        memset(f, 0, sizeof f);
        f[0][0][0][0][0] = 1;
        int t = 0;

        int res = 0, x[4];
        FOR(i,0,h) next[i] = min(i+1, h);

        FOR(i,0,n) {
            memset(f[1-t], 0, sizeof f[1-t]);

            FOR(a,0,h) FOR(b,a,h) FOR(c,b,h) FOR(d,c,h) if (f[t][a][b][c][d])
            if (a < h || b < h || c < h || d < h) {
                x[0] = next[b];
                x[1] = next[c];
                x[2] = next[d];
                sort(x, x+3);
                if (a < h)
                    update(f[1-t][0][x[0]][x[1]][x[2]], f[t][a][b][c][d]);
                else update(f[1-t][x[0]][x[1]][x[2]][h], f[t][a][b][c][d]);

                x[0] = next[a];
                x[1] = next[c];
                x[2] = next[d];
                sort(x, x+3);
                if (b < h)
                    update(f[1-t][0][x[0]][x[1]][x[2]], f[t][a][b][c][d]);
                else update(f[1-t][x[0]][x[1]][x[2]][h], f[t][a][b][c][d]);

                x[0] = next[a];
                x[1] = next[b];
                x[2] = next[d];
                sort(x, x+3);
                if (c < h)
                    update(f[1-t][0][x[0]][x[1]][x[2]], f[t][a][b][c][d]);
                else update(f[1-t][x[0]][x[1]][x[2]][h], f[t][a][b][c][d]);

                x[0] = next[a];
                x[1] = next[b];
                x[2] = next[c];
                if (d < h)
                    update(f[1-t][0][x[0]][x[1]][x[2]], f[t][a][b][c][d]);
                else update(f[1-t][x[0]][x[1]][x[2]][h], f[t][a][b][c][d]);

                if (i == n) {
                    update(res, f[t][a][b][c][d]);
                }
            }

            t = 1 - t;
        }

        cout << res << endl;
    }
    return 0;
}
