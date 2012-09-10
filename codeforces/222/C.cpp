
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
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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
const long long MAXV = 10000000;
const int MAXP = 700111;
const int MN = 100111;

bool sieve[MAXV + 111];
int nprime, prime[MAXP], tu[MAXP], mau[MAXP];
int n, m;
int a[MN], b[MN];

void init() {
    FOR(i,2,3200) if (!sieve[i]) {
        int j = i*i;
        while (j <= MAXV) {
            sieve[j] = 1;
            j += i;
        }
    }
    FOR(i,2,MAXV) if (!sieve[i]) prime[++nprime] = i;
}

void update(int x, int a[]) {
    int cnt;
    for(int i = 1; prime[i] * prime[i] <= x; ++i) if (x % prime[i] == 0) {
        cnt = 0;
        while (x % prime[i] == 0) {
            x /= prime[i];
            ++cnt;
        }
        a[i] += cnt;
    }
    if (x > 1) {
        int i = lower_bound(prime+1, prime+nprime+1, x) - prime;
        a[i]++;
    }
}

int ra[MN], rb[MN], sa, sb;

void get(int x, int &sz, int r[], int g[]) {
    int cnt;
    int res = 1, save = x;
    for(int i = 1; prime[i] * prime[i] <= x; ++i) if (x % prime[i] == 0) {
        cnt = 0;
        while (x % prime[i] == 0) {
            x /= prime[i];
            ++cnt;
        }
        int reduce = min(g[i], cnt);
        g[i] -= reduce;
        cnt -= reduce;
        while (cnt--) res = res * prime[i];
    }
    if (x > 1) {
        int i = lower_bound(prime+1, prime+nprime+1, x) - prime;
        cnt = 1;
        int reduce = min(g[i], cnt);
        g[i] -= reduce;
        cnt -= reduce;
        while (cnt--) res = res * prime[i];
    }
    ++sz;
    r[sz] = res;
}

int main() {
    init();
    GN(n); GN(m);
    FOR(i,1,n) GN(a[i]);
    FOR(i,1,m) GN(b[i]);

    FOR(i,1,n) update(a[i], tu);
    FOR(j,1,m) update(b[j], mau);

    FOR(i,1,nprime) tu[i] = mau[i] = min(tu[i], mau[i]);

    // FOR(i,1,nprime) if (tu[i]) cout << prime[i] << "^" << tu[i] << "   "; cout << endl;
    // FOR(i,1,nprime) if (mau[i]) cout << prime[i] << "^" << mau[i] << "   "; cout << endl;
    // FOR(i,1,nprime) if (g[i]) cout << prime[i] << "^" << g[i] << "   "; cout << endl;

    sa = sb = 0;
    FOR(i,1,n) get(a[i], sa, ra, tu);
    FOR(j,1,m) get(b[j], sb, rb, mau);

    printf("%d %d\n", sa, sb);
    FOR(i,1,sa) printf("%d ", ra[i]); puts("");
    FOR(i,1,sb) printf("%d ", rb[i]); puts("");
    return 0;
}
