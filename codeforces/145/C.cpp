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
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

int INP,AM;
#define BUFSIZE (1<<10)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF,0,sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

const double PI = acos(-1.0);
const int BASE = 1000000007;

bool lucky(int n) {
    while (n) {
        int cur = n % 10;
        if (cur != 4 && cur != 7) return false;
        n /= 10;
    }
    return true;
}

int power(ll x, int k) {
    if (!k) return 1;
    if (k == 1) return x % BASE;
    ll mid = power(x, k >> 1);
    mid = (mid * mid) % BASE;
    if (k & 1) return (mid * x) % BASE;
    else return mid;
}

inline int inv(int x) {
    return power(x, BASE - 2);
}

int a[100111], x[2011], cnt[2011];
int f[2011][2011];
int n0, n, n1;
int fact[100111], invfact[100111];

void init() {
    fact[0] = 1;
    FOR(i,1,100000) fact[i] = (fact[i-1] * (ll)i) % BASE;
    
    invfact[0] = 1;
    FOR(i,1,100000) invfact[i] = (invfact[i-1] * (ll) inv(i)) % BASE;
}

int c(int n, int k) {
    ll res = fact[n];
    res = (res * invfact[k]) % BASE;
    res = (res * invfact[n-k]) % BASE;
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    init();
    int k; scanf("%d%d", &n, &k);
    FOR(i,1,n) scanf("%d", &a[i]);
    sort(a+1, a+n+1);
    
    FOR(i,1,n)
    if (lucky(a[i])) {
        if (n1 && x[n1] == a[i]) cnt[n1]++;
        else {
            n1++;
            x[n1] = a[i];
            cnt[n1] = 1;
        }
    }
    else n0++;
    
    f[0][0] = 1;
    FOR(i,1,n1) {
        f[i][0] = 1;
        FOR(k,1,i) {
            f[i][k] = (f[i-1][k] + f[i-1][k-1] * (ll) cnt[i]) % BASE;
        }
    }
    
    int res = 0;
    FOR(a,0,n0) {
        int b = k - a;
        if (0 <= b && b <= n1) {
//            cout << n0 << ' ' << a << ' ' << c(n0, a) << ' ' << f[n1][b] << endl;
            res = (res + c(n0,a) * (ll) f[n1][b]) % BASE;
        }
    }
    cout << res;
    return 0;
}
