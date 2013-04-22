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

int n;
char x[2000111], y[2000111];

int main() {
    string a, b;
    while (scanf("%d\n", &n) == 1) {
        gets(x); gets(y);
        int c00 = 0, c01 = 0, c10 = 0, c11 = 0;
        REP(i,n*2) {
            if (x[i] == '0') {
                if (y[i] == '0') ++c00;
                else ++c01;
            }
            else {
                if (y[i] == '0') ++c10;
                else ++c11;
            }
        }
        a = ""; b = "";
        REP(turn,n) {
            if (c11) {
                --c11; a += '1';
            }
            else if (c10) {
                --c10; a += '1';
            }
            else if (c01) {
                --c01; a += '0';
            }
            else {
                --c00; a += '0';
            }

            if (c11) {
                --c11; b += '1';
            }
            else if (c01) {
                --c01; b += '1';
            }
            else if (c10) {
                --c10; b += '0';
            }
            else {
                --c00; b += '0';
            }
        }

        if (a == b) puts("Draw");
        else if (a > b) puts("First");
        else puts("Second");
        break;
    }
    return 0;
}
