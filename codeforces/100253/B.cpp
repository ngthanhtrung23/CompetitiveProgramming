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

const int MN = 300111;

int m, n, r;
long long c[MN], x[MN], gh;

long long read() {
    int a, b;
    scanf("%d.%d", &a, &b);
    return a * 10 + b;
}

inline long long sqr(long long x) {
    return x * x;
}

int getLowest(int l, int r, int x) {
    int res = r;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (c[mid] >= x || sqr(x - c[mid]) <= gh) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

int getHighest(int l, int r, int x) {
    int res = l;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (c[mid] <= x || sqr(x - c[mid]) <= gh) {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return res;
}

int main() {
    while (scanf("%d%d%d", &m, &n, &r) == 3) {
        gh = (r * r - 1) * 100;

        FOR(i,1,m) c[i] = read();
        FOR(i,1,n) x[i] = read();

        int cur = 1, next;
        long long res = 0;
        FOR(i,1,n) {
            if (x[i] >= c[cur]) {
                next = getLowest(cur, m, x[i]);
            }
            else {
                next = getHighest(1, cur, x[i]);
            }
            res += llabs(c[next] - c[cur]);
            cur = next;
        }
        cout << res/10 << '.' << res%10 << endl;
    }
    return 0;
}
