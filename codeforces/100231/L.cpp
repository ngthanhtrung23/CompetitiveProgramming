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

int len[70];
long long f[70][2][70];
int bound[70];

long long get(long long r, int k) {
    if (r <= 0) return 0;

    memset(bound, 0, sizeof bound);

    for(int i = 1; i <= 61; ++i)
        bound[i] = (r >> (61LL - i)) & 1LL;

    memset(f, 0, sizeof f);
    f[0][0][0] = 1;

    FOR(i,0,60) FOR(lower,0,1) FOR(cnt,0,i) if (f[i][lower][cnt]) {
        FOR(cur,0,1)
        if (cur <= bound[i+1] || lower) {
            int lower2 = lower; if (cur < bound[i+1]) lower2 = 1;
            int cnt2 = cnt + cur;
            f[i+1][lower2][cnt2] += f[i][lower][cnt];
        }
    }

    return f[61][0][k] + f[61][1][k];
}

int main() {
    FOR(i,1,61) {
        len[i] = 0;
        int u = i;
        while (u > 1) {
            u = __builtin_popcountll(u);
            ++len[i];
        }
    }
    // PR(len, 61);
    long long l, r;
    int x;
    while (cin >> l >> r >> x) {
        if (l == 0 && r == 0 && x == 0) break;

        // int cnt = 0;
        // for(long long t = l; t <= r; ++t) {
        //     long long u = t;
        //     int len = 0;
        //     while (u > 1) u = __builtin_popcountll(u), ++len;
        //     if (len == x) ++cnt;
        // }
        // cout << cnt << endl;

        if (x == 0) {
            if (l <= 1) cout << 1 << endl;
            else cout << 0 << endl;
            continue;
        }

        if (l == 1) ++l;

        long long res = 0;
        FOR(nbit,1,61)
        if (len[nbit] + 1 == x) {
            res += get(r, nbit) - get(l - 1, nbit);
        }
        cout << res << endl;
    }
    return 0;
}
