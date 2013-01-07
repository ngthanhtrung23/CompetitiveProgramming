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
const int MN = 100111;

int n, a[MN];

bool inc() {
    FOR(i,2,n) if (a[i] < a[i-1]) return false;
    return true;
}

bool dec() {
    FOR(i,2,n) if (a[i] > a[i-1]) return false;
    return true;
}

bool check() {
    return !inc() && !dec();
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        bool ok = false;

        int x = -1, y = -1, z = -1;
        FOR(i,1,n) {
            if (x < 0) x = i;
            else if (a[i] != a[x]) {
                if (y < 0) y = i;
                else if (a[i] != a[y]) {
                    if (z < 0) z = i;
                }
            }
        }

        if (z < 0 && y > 0) {
            FOR(i,1,n) if (i != x && i != y) {
                z = i;
                break;
            }
        }

        // PR(a, n);
        // cout << x << ' ' << y << ' ' << z << endl;

        if (y < 0 && z < 0) puts("-1");
        else {
            swap(a[x], a[y]);
            if (a[x] != a[y] && check()) cout << x << ' ' << y << endl;
            else if (z < 0) puts("-1");
            else {
                swap(a[x], a[y]);

                swap(a[x], a[z]);
                if (a[x] != a[z] && check()) cout << x << ' ' << z << endl;
                else {
                    swap(a[z], a[x]);

                    swap(a[y], a[z]);
                    if (a[y] != a[z] && check()) cout << y << ' ' << z << endl;
                    else puts("-1");
                }
            }
        }
    }
    return 0;
}
