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
const long long oo = 1000111000111000LL;

long long f[MN], v[MN];
long long it[MN];
int c[MN], n, q;

pair<long long, long long> best[2];

long long getMax(long long color) {
    if (color > 0) {
        return it[color];
    }
    else {
        color = -color;
        if (best[0].S == color) return best[1].F;
        else return best[0].F;
    }
}

void update(long long color, long long value) {
    it[color] = max(it[color], value);

    if (it[color] > best[0].F) {
        if (best[0].S != color) {
            best[1] = best[0];
            best[0] = MP(it[color], color);
        }
        else best[0] = MP(it[color], color);
    }
    else if (it[color] > best[1].F) {
        if (best[0].S != color) {
            best[1] = MP(it[color], color);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            v[i] = x;
        }
        FOR(i,1,n) scanf("%d", &c[i]);

        int a, b;
        while (q--) {
            scanf("%d%d", &a, &b);
            long long res = 0;
            FOR(i,1,n) it[i] = -oo;

            best[0] = MP(-oo, 0);
            best[1] = MP(-oo, -1);

            FOR(i,1,n) {
                f[i] = v[i] * b;
                f[i] = max(f[i], getMax(c[i]) + v[i] * a);
                f[i] = max(f[i], getMax(-c[i]) + v[i] * b);

                res = max(res, f[i]);
                update(c[i], f[i]);
            }

            // PR(f, n);
            cout << res << endl;
        }
    }
    return 0;
}