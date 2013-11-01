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

const int MN = 5011;
int n;
struct Seg {
    int l, r, val;
} a[MN];

bool operator < (const Seg &a, const Seg &b) {
    if (a.l != b.l) return a.l < b.l;
    if (a.r != b.r) return a.r > b.r;
    return a.val < b.val;
}

int f[MN][MN*2], c[MN*2], start[MN];

void update(int &x, int val) {
    x = max(x, val);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int now = 0;
        FOR(i,1,n) {
            cin >> a[i].l >> a[i].r >> a[i].val;
            a[i].r += a[i].l;
            c[++now] = a[i].l;
            c[++now] = a[i].r;
        }
        sort(c+1, c+now+1);
        now = unique(c+1, c+now+1) - c - 1;
        // PR(c, now);
        FOR(i,1,n) {
            a[i].l = lower_bound(c+1, c+now+1, a[i].l) - c;
            a[i].r = lower_bound(c+1, c+now+1, a[i].r) - c;
        }
        sort(a+1, a+n+1);
        memset(f, 0, sizeof f);

        FOR(i,1,n) {
            start[i] = n+1;
            FOR(j,i+1,n)
            if (a[j].l >= a[i].r) {
                start[i] = j;
                break;
            }
        }
        // FOR(i,1,n) cout << a[i].l << ' ' << a[i].r << ' ' << a[i].val << endl;
        // PR(start, n);

        FORD(i,n,1) {
            FOR(j,1,now) f[i][j] = f[i+1][j];

            update(f[i][a[i].r], f[i+1][a[i].r] + a[i].val);

            if (start[i] <= n) {
                FOR(x,a[i].r+1,now) {
                    update(f[i][x], f[i][a[i].r] + f[start[i]][x]);
                }
            }

            FOR(j,1,now) f[i][j] = max(f[i][j], f[i][j-1]);
        }
        cout << f[1][now] << endl;
    }
    return 0;
}
