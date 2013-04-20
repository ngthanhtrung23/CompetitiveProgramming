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

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

int n, m, k, t, MOD;
int nPrime, primes[600111], sieve[600111];
long long f[33][33], g[33][33], dp[33][33];
pair<int,int> a[33];

void init() {
    FOR(i,2,800) if (!sieve[i]) {
        int j = i*i;
        while (j <= 600000) {
            sieve[j] = i;
            j += i;
        }
    }
    FOR(i,2,600000) if (!sieve[i]) primes[++nPrime] = i;
    // PR(primes, 100);
    // DEBUG(nPrime);
}

int get(int p, int n) {
    int res = 0;
    while (n >= p) {
        res += n/p;
        n /= p;
    }
    return res;
}

int power(int x, int k) {
    if (k == 0) return 1 % MOD;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % MOD;

    if (k & 1) return (mid * x) % MOD;
    else return mid;
}

int C(int n, int k) {
    long long res = 1;
    FOR(i,1,nPrime) {
        int p = primes[i];
        if (p > n) break;
        int x = get(p, n) - get(p, k) - get(p, n-k);

        if (x > 0) res = (res * power(p, x)) % MOD;
    }
    return (int) res;
}

int main() {
    freopen("turtle.in", "r", stdin);
    freopen("turtle.out", "w", stdout);
    init();
    while (scanf("%d%d%d%d%d", &n, &m, &k, &t, &MOD) == 5) {
        FOR(i,2,k+1) scanf("%d%d", &a[i].first, &a[i].second);
        a[1] = MP(0,0);
        a[k+2] = MP(n,m);
        k = k + 2;
        sort(a+1, a+k+1);
        // FOR(i,1,k) cout << a[i].first << ' ' << a[i].second << endl;

        memset(f, 0, sizeof f); memset(g, 0, sizeof g);

        FORD(i,k,1) FOR(j,i+1,k)
        if (a[i].first <= a[j].first && a[i].second <= a[j].second) {
            int dx = a[j].first - a[i].first;
            int dy = a[j].second - a[i].second;

            g[i][j] = C(dx+dy, dx);
            f[i][j] = g[i][j];
            FOR(k,i+1,j-1)
                f[i][j] = ((f[i][j] - f[i][k] * (long long) g[k][j]) % MOD + MOD) % MOD;
        }
        memset(dp, 0, sizeof dp);
        dp[1][0] = 1;

        FOR(i,1,k-1) FOR(u,0,t) if (dp[i][u]) {
            FOR(j,i+1,k) {
                dp[j][u+1] = (dp[j][u+1] + f[i][j] * (long long) dp[i][u]) % MOD;
            }
        }

        int res = 0;
        FOR(u,1,t+1)
            res = (res + dp[k][u]) % MOD;
        cout << res << endl;
    }
    return 0;
}
