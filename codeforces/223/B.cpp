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
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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
const int MN = 200111;

char tmp[MN];
string a, b;
int f[2][MN], g[2][MN];
int next[30][MN], prev[30][MN];

int main() {
    while (gets(tmp)) {
        a = ' ' + string(tmp);
        gets(tmp); b = ' ' + string(tmp);
        int la = a.length()-1, lb = b.length()-1;

        memset(f, -1, sizeof f); memset(g, -1, sizeof g);
        FOR(c,0,'z'-'a') {
            prev[c][0] = 0;
            FOR(i,1,lb) {
                if (b[i]-'a' == c) prev[c][i] = i;
                else prev[c][i] = prev[c][i-1];
            }

            next[c][lb+1] = lb+1;
            FORD(i,lb,1) {
                if (b[i]-'a' == c) next[c][i] = i;
                else next[c][i] = next[c][i+1];
            }
        }

        f[0][0] = f[1][0] = 0;
        int can;
        FOR(i,1,la) {
            f[0][i] = max(f[0][i-1], f[1][i-1]);
            can = f[0][i] + 1; if (can > lb) --can;
            f[1][i] = prev[a[i]-'a'][can];
        }

        g[0][la+1] = g[1][la+1] = lb+1;
        FORD(i,la,1) {
            g[0][i] = min(g[0][i+1], g[1][i+1]);
            can = g[0][i] - 1; if (can < 1) ++can;
            g[1][i] = next[a[i]-'a'][can];
        }

        // PR(f[0], la);
        // PR(f[1], la);

        // PR(g[0], la);
        // PR(g[1], la);

        bool ok = true;
        FOR(i,1,la)
            if (f[1][i] > 0 && f[1][i] >= g[0][i] - 1) {
            }
            else ok = false;

        if (ok) puts("Yes");
        else puts("No");
    }
    return 0;
}
