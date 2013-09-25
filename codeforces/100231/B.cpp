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

struct Seg {
    int a, b, c;
} x[50111];

bool operator < (const Seg &u, const Seg &v) {
    if (u.b != v.b) return u.b < v.b;
    else if (u.a != v.a) return u.a < v.a;
    else return u.c < v.c;
}

int bit[50111], n;
bool mark[50111];

#define _(x) ((x) & (-(x)))

int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= _(x))
        res += bit[x];
    return res;
}

void update(int u) {
    for(int x = u; x <= 50000; x += _(x))
        ++bit[x];
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> x[i].a >> x[i].b >> x[i].c;
        sort(x+1, x+n+1);
        // FOR(i,1,n) cout << x[i].a << ' ' << x[i].b << ' ' << x[i].c << endl;

        memset(bit, 0, sizeof bit);
        memset(mark, 0, sizeof mark);

        int res = 0;
        FOR(i,1,n) {
            int has = get(x[i].b) - get(x[i].a - 1);
            if (has >= x[i].c) continue;

            int u = x[i].b;
            REP(turn,x[i].c - has) {
                while (mark[u]) --u;
                mark[u] = true;
                update(u);
            }
            res += x[i].c - has;
        }
        cout << res << endl;
    }
    return 0;
}
