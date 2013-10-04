#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

int a[2011], bit[2][2011], c[2011], n, b[2011];

#define _(x) ((x) & (-(x)))
int get(int t, int u) {
    int res = 0;
    for(; u > 0; u -= _(u))
        res += bit[t][u];
    return res;
}

void update(int t, int u, int val) {
    for(; u <= n; u += _(u))
        bit[t][u] += val;
}

int count() {
    int res = 0;
    memset(bit, 0, sizeof bit);
    FORD(i,n,1) {
        res += get(0, a[i] - 1);
        update(0, a[i], 1);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i], b[i] = a[i];

        while (true) {
            FOR(i,1,n) a[i] = b[i];

            FOR(i,1,n) c[i] = a[i];
            sort(c+1, c+n+1);
            int s = unique(c+1, c+n+1) - c - 1;
            c[++s] = 1000111000;
            c[0] = -1000111000;
            // PR(c, s);
            FOR(i,1,n) a[i] = lower_bound(c+1, c+s+1, a[i]) - c;
            // PR(a, n);

            int cur = count();
            // DEBUG(cur);

            bool good = false;
            FOR(i,1,n) {
                int add = 0;
                update(0, a[i], -1);

                add -= get(0, a[i] - 1);
                add += get(0, lower_bound(c+1, c+s+1, -b[i]) - c - 1);

                add -= i - 1 - get(1, a[i]);
                add += i - 1 - get(1, upper_bound(c+1, c+s+1, -b[i]) - c - 1);

                update(1, a[i], 1);

                if (add < 0) {
                    b[i] = -b[i];
                    good = true;
                    break;
                }
            }
            if (!good) break;
        }
        cout << count() << endl;
    }
    return 0;
}
