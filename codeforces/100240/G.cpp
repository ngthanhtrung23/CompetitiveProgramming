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

const int MN = 100111;

pair<int,int> a[MN];
int bit[MN], f[MN];

#define _(x) ((x) & (-(x)))
int get(int x) {
    int res = 0;
    for(; x > 0; x -= _(x))
        res = max(res, bit[x]);
    return res;
}

void update(int x, int val) {
    for(; x <= 10000; x += _(x))
        bit[x] = max(bit[x], val);
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
            a[i].second = -a[i].second;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) {
            a[i].second = -a[i].second;
            a[i].second = 10000 - a[i].second + 1;
        }

        memset(bit, 0, sizeof bit);
        int res = 0;
        FOR(i,1,n) {
            f[i] = get(a[i].second) + 1;
            update(a[i].second, f[i]);
            res = max(res, f[i]);
        }
        cout << res << endl;
    }
    return 0;
}
