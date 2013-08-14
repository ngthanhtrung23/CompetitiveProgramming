#include <bits/stdc++.h>

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
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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
const int MOD = 1000000007LL;
const int MN = 200111;

long long gt[MN], revgt[MN];

long long power(long long u, int k) {
    if (k == 0) return 1;
    if (k == 1) return u;
    long long mid = power(u, k >> 1);
    mid = mid * mid % MOD;
    if (k & 1) return mid * u % MOD;
    else return mid;
}

long long c(int n, int k) {
    if (k < 0 || k > n) return 0;
    return gt[n] * revgt[k] % MOD * revgt[n-k] % MOD;
}

long long get(int a, int b, int g) {
    if (a < 0 || b < 0) return 0;

    if (a + b == 1) {
        if (g == 0 && a == 1) return 1;
        if (g == 1 && b == 1) return 1;
        return 0;
    }
    if (g == 1) return get(a-1, b, 0);
    if (g == 0) return (get(a-1, b, 1) + c(a+b-1, a)) % MOD;
    return 0;
}

int main() {
    gt[0] = 1; revgt[0] = 1;
    FOR(i,1,200000) {
        gt[i] = (gt[i-1] * i) % MOD;
        revgt[i] = power(gt[i], MOD - 2);
    }
    int a, b, g;
    while (cin >> a >> b >> g) {
        cout << get(a, b, g) << endl;
    }
    return 0;
}
