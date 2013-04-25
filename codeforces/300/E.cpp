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
const int MN = 11000111;

int sieve[MN], has[MN], id[MN];
int nPrime, prime[MN/10];
long long need[MN/10];

void init() {
    FOR(i,2,4000) if (!sieve[i]) {
        int j = i*i;
        while (j <= 10000000) {
            sieve[j] = i;
            j += i;
        }
    }
    FOR(i,2,10000000)
        if (!sieve[i]) {
            ++nPrime;
            prime[nPrime] = i;
            id[i] = nPrime;
        }
}

long long get(long long p, long long n) {
    long long res = 0;
    while (n >= p) {
        res += n / p;
        n /= p;
    }
    return res;
}

bool check(long long n) {
    FOR(i,1,nPrime) {
        int p = prime[i];
        long long has = get(p, n);
        if (has < need[i]) return false;
    }
    return true;
}

int main() {
    init();
    int k;
    while (scanf("%d", &k) == 1) {
        long long l = 0, r = 0;
        FOR(i,1,k) {
            int a; scanf("%d", &a);
            l = max(l, (long long) a);
            r += a;

            has[a]++;
        }
        FORD(i,10000000,1)
            has[i] += has[i+1];
        FOR(a,2,10000000) {
            int savea = a;
            while (sieve[a]) {
                int p = sieve[a];
                while (a % p == 0) {
                    a /= p;
                    need[id[p]] += has[savea];
                }
            }
            if (a > 1) need[id[a]] += has[savea];
            a = savea;
        }
        // PR(prime, 10);
        // PR(need, 10);
        long long res = r;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
