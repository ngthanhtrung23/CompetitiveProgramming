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

char a[55][55], b[55][55];
int ma, na, mb, nb;

int main() {
    while (scanf("%d%d\n", &ma, &na) == 2) {
        FOR(i,1,ma) scanf("%s\n", &a[i][1]);
        scanf("%d%d\n", &mb, &nb);
        FOR(i,1,mb) scanf("%s\n", &b[i][1]);

        long long best = 0;
        int savex = -1, savey = -1;
        FOR(x,-ma,mb) FOR(y,-na,nb) {
            long long cur = 0;
            FOR(i,1,ma) FOR(j,1,na) {
                int ii = i + x, jj = j + y;
                if (ii < 1 || ii > mb || jj < 1 || jj > nb) continue;

                cur += (a[i][j]-'0') * (b[ii][jj]-'0');
            }
            if (cur > best) {
                best = cur;
                savex = x;
                savey = y;
            }
        }
        cout << savex << ' ' << savey << endl;
    }
    return 0;
}
