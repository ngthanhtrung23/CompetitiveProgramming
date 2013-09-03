#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

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

const long long MOD = 1000000007;
const int MN = 1000111;

#define _(x) ((x) & (-(x)))

int n;
long long a[MN], sum[MN], bit[MN];

void update(int u, int k) {
    for(int x = u; x <= 1000000; x += _(x))
        bit[x] = (bit[x] + k) % MOD;
}

long long get(int u) {
    long long res = 0;
    for(int x = u; x > 0; x -= _(x))
        res = (res + bit[x]) % MOD;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) cin >> a[i];

        long long res = 0;
        FOR(i,1,n) {
            sum[i] = (a[i] + get(a[i]) * a[i] - get(a[i]) + MOD + get(a[i]-1)) % MOD;

            res = (res + sum[i]) % MOD;
            update(a[i], sum[i]);
        }
        cout << res << endl;
    }
    return 0;
}
