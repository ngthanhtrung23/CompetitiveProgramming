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
const int MN = 100111;

long long f[MN], g[MN], h[MN], sz[MN], s[MN], s2[MN], first[MN];

long long solve(string x) {
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    memset(h, 0, sizeof h);
    memset(sz, 0, sizeof sz);
    memset(s, 0, sizeof s);
    memset(s2, 0, sizeof s2);
    memset(first, 0, sizeof first);

    int n = x.length();
    FOR(i,1,n) {
        int cur = x[i-1] - '0';
        s[i] = (s[i-1] * 10 + cur) % MOD;
        s2[i] = (s2[i-1] * 100 + cur * cur + cur * 20 * s[i-1]) % MOD;
    }

    sz[0] = 1;
    FOR(i,1,n) {
        first[i] = (first[i-1] * 10 + 4) % MOD;
        sz[i] = sz[i-1] * 2 % MOD;
        h[i] = (h[i-1] * 20 + 11 * sz[i-1]) % MOD;
        g[i] = (g[i-1] * 200 + 220 * h[i-1] + sz[i-1] * (4*4 + 7*7)) % MOD;
        f[i] = (g[i-1] * 100 + 220 * h[i-1] + f[i-1] * 100 + (2*sz[i-1] - 1) * 28 - first[i-1] * 70 - s[i-1] * 40 + MOD * 111) % MOD;

        if (x[i-1] == '4') {
            sz[i] = (sz[i] - 1 + MOD) % MOD;
            h[i] = (h[i] - s[i] - 3 + MOD * 2) % MOD;
            g[i] = (g[i] - s2[i] - 6*s[i] - 9 + MOD * 8) % MOD;
            f[i] = (f[i] - s2[i] - 3*s[i] + MOD * 4) % MOD;
        }
    }

    // PR(s, n);
    // PR(s2, n);
    // PR(sz, n);
    // PR(first, n);
    // PR(h, n);
    // PR(g, n);
    // PR(f, n);

    return f[n];
}

char a[100111];

bool sub1(string &l) {
    REP(i,l.length())
        if (l[i] == '7') return true;
    return false;
}

int main() {
    while (gets(a)) {
        string l = string(a);
        gets(a); string r = string(a);

        long long res = solve(r);
        if (sub1(l)) {
            res = (res - solve(l) + MOD) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}
