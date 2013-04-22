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

long long p[100111], k[100111], has[100111];
long long n, res;
int cnt;

void check(long long x, long long y, long long z) {
    if ((x + y - z) & 1) return ;

    if (x+y > z && y+z > x && z+x > y) ++res;
}

void attempt2(int i, long long y, long long x) {
    if (i > cnt) {
        long long z = n / x / y;
        check(x, y, z);
        return ;
    }
    long long cur = 1;
    FOR(now,0,has[i]) {
        attempt2(i+1, y*cur, x);
        cur *= p[i];
    }
}

void attempt1(int i, long long x) {
    if (i > cnt) {
        attempt2(1, 1, x);
        return ;
    }
    long long cur = 1;
    FOR(now,0,k[i]) {
        has[i] = k[i] - now;
        attempt1(i+1, x * cur);
        cur = cur * p[i];
    }
}

int main() {
    while (cin >> n) {
        memset(k, 0, sizeof k);
        memset(p, 0, sizeof p);

        if (n % 3) {
            puts("0");
            continue;
        }
        res = 0;
        n /= 3;
        long long saven = n;
        cnt = 0;
        for(long long x = 2; x*x <= n; ++x) if (n % x == 0) {
            ++cnt;
            p[cnt] = x;
            while (n % x == 0) {
                ++k[cnt];
                n /= x;
            }
        }
        if (n > 1) {
            ++cnt;
            p[cnt] = n;
            k[cnt] = 1;
        }
        n = saven;
        attempt1(1, 1);
        cout << res << endl;
    }
    return 0;
}
