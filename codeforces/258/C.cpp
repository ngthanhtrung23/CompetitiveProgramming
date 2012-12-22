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
const long long MOD = 1000000007;

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = mid * mid % MOD;

    if (k & 1) return (mid * x) % MOD;
    else return mid;
}

int n, a[100111];
int uoc[100111], nUoc;

int get(int x) {
    if (x > a[n]) return 0;
    int i = lower_bound(a+1, a+n+1, x) - a;
    return n - i + 1;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        int ln = a[1];
        FOR(i,2,n) ln = max(ln, a[i]);
        sort(a+1, a+n+1);

        long long res = 0;
        FOR(lcm, 1, ln) {
            nUoc = 0;
            for(int i = 1; i * i <= lcm; ++i)
                if (lcm % i == 0) {
                    uoc[++nUoc] = i;
                    if (lcm != i*i) uoc[++nUoc] = lcm / i;
                }

            sort(uoc+1, uoc+nUoc + 1);
            // PR(uoc, nUoc);

            int last = 0;
            long long now = 1;
            FORD(i,nUoc,1) {
                int t = get(uoc[i]);
                if (i == nUoc) {
                    now = now * (power(i, t) - power(i-1, t) + MOD) % MOD;
                }
                else {
                    now = now * (power(i, t-last)) % MOD;
                }
                last = t;
            }
            res = (res + now) % MOD;
            // cout << lcm << ' ' << res << endl;
        }
        cout << res << endl;
    }
    return 0;
}
