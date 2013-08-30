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

int n, m;
long long sum[2][2][1011][1011], a[1011][1011];

#define _(x) ((x) & (-(x)))

void update(int u, int v, long long val) {
    if (u <= 0 || v <= 0) return ;

    a[u][v] ^= val;

    for(int x = u; x <= n; x += _(x))
        for(int y = v; y <= n; y += _(y))
            sum[u&1][v&1][x][y] ^= val;
}

long long bitget(int u, int v, int a, int b) {
    long long res = 0;
    for(int x = u; x > 0; x -= _(x))
        for(int y = v; y > 0; y -= _(y)) {
            if (a == 1 && b == 1)
                res ^= sum[1][1][x][y];
            else if (a == 0 && b == 1)
                res ^= sum[0][1][x][y] ^ sum[1][1][x][y];
            else if (a == 1 && b == 0)
                res ^= sum[1][0][x][y] ^ sum[1][1][x][y];
            else
                res ^= sum[0][0][x][y] ^ sum[0][1][x][y]
                     ^ sum[1][0][x][y] ^ sum[1][1][x][y];
        }
    return res;
}

long long get(int u, int v) {
    long long res = 0;
    res = bitget(u, v, 1, 1);
    if (v & 1) res ^= bitget(u-1, n, 1, 0) ^ bitget(u-1, v, 1, 0);
    if (u & 1) res ^= bitget(n, v-1, 0, 1) ^ bitget(u, v-1, 0, 1);
    if ((u & 1) && (v & 1))
        res ^= bitget(n, n, 0, 0)
                ^ bitget(u-1, n, 0, 0)
                ^ bitget(n, v-1, 0, 0)
                ^ bitget(u-1, v-1, 0, 0)
                ^ a[u][v];
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        while (m--) {
            int type, x1, x2, y1, y2;
            cin >> type >> x1 >> y1 >> x2 >> y2;

            if (type == 1) {
                long long sum = get(x2, y2) ^ get(x1-1, y2) ^ get(x2, y1-1) ^ get(x1-1, y1-1);
                printf("%I64d\n", sum);
            }
            else {
                long long val; cin >> val;
                update(x2, y2, val);
                update(x1-1, y2, val);
                update(x2, y1-1, val);
                update(x1-1, y1-1, val);
            }
        }
    }
    return 0;
}
