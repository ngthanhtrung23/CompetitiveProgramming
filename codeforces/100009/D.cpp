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

set<long long> s;
string a[120111];
int n;
char tmp[1000111];
long long h[1000111];

long long power(long long x, long long k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1LL);
    mid = (mid*mid) % MOD;
    if (k & 1) return (mid * x) % MOD;
    return mid;
}

long long inv = power(31, MOD - 2);

int main() {
    while (gets(tmp) && strlen(tmp)) {
        ++n;
        a[n] = string(tmp);
    }
    FOR(t,1,n) {
        long long v = 0, last = 0, p = 1;
        REP(i,a[t].length()) {
            v = (last + (a[t][i] - 'a'+1)*p) % MOD;
            last = v; p = (p * 31) % MOD;
        }
        s.insert(v);
    }
    int res = 0;
    FOR(t,1,n) {
        long long p = 1, last = 0;
        REP(i,a[t].length()) {
            h[i] = (last + (a[t][i] - 'a'+1)*p) % MOD;
            last = h[i];
            p = (p * 31) % MOD;
        }
        
        long long v = 0;
        int l = a[t].length(); last = 0, p = 1;
        REP(i,a[t].length()-1) {
            v = (last + (a[t][i] - 'a'+1) * p) % MOD;
            last = v; p = (p * 31) % MOD;
            
            long long h2 = (h[l-1] - h[i] + MOD) % MOD * power(inv, i+1) % MOD;
            if (s.find(v) != s.end() && s.find(h2) != s.end()) {
                cout << a[t] << endl;
                break;
            }
        }
    }
    return 0;
}
