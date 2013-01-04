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
const long long MOD = 1000000007LL;

int area(int x1, int y1, int x2, int y2) {
    return x1*y2 - x2*y1;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = mid * mid % MOD;
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long inv(long long x) {
    return power(x, MOD - 2);
}

int get(int x, int n) {
    if (n % 2 != x) --n;
    return (n - x) / 2 + 1;
}

int main() {
    int w, h;
    while (cin >> w >> h) {
        long long res = 0;

        REP(x1,2) REP(y1,2)
        REP(x2,2) REP(y2,2)
        REP(x3,2) REP(y3,2)
        if (MP(x1,y1) <= MP(x2,y2) && MP(x2,y2) <= MP(x3,y3))
            if (area(x2-x1, y2-y1, x3-x1, y3-y1) % 2 == 0) {
                ll can1 = get(x1, w) * get(y1, h);
                ll can2 = get(x2, w) * get(y2, h);
                ll can3 = get(x3, w) * get(y3, h);

                if (MP(x1,y1) == MP(x2,y2)) --can2;
                if (MP(x1,y1) == MP(x3,y3)) --can3;
                if (MP(x2,y2) == MP(x3,y3)) --can3;

                if (can2 <= 0) continue;
                if (can3 <= 0) continue;

                if (MP(x1,y1) == MP(x2,y2) && MP(x1,y1) == MP(x3,y3))
                    res = (res + can1 * can2 % MOD * can3) % MOD;
                else if (MP(x1,y1) == MP(x2,y2) || MP(x1,y1) == MP(x3,y3) || MP(x2,y2) == MP(x3,y3))
                    res = (res + can1 * can2 % MOD * can3 % MOD * 3) % MOD;
                else res = (res + can1 * can2 % MOD * can3 % MOD * 6) % MOD;
            }

        // DEBUG(res);

        FOR(x,-w,w) FOR(y,0,h)
        if (y > 0 || x > 0) {
            int g = gcd(abs(x), y) - 1;

            if (g > 0) {
                res -= (w - abs(x) + 1) * (h - abs(y) + 1) % MOD * g * 6 % MOD;

                if (res < 0) res += MOD;
            }
        }
        cout << res << endl;
    }
    return 0;
}
