
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int n, d;
ll a[100111], w[100111];

bool check(ll val) {
    w[1] = val;
    ll bound = a[1] + d * (2 * w[1] - val);

    FOR(i,2,n) {
        w[i] = min(((bound - a[i]) / d + val) / 2, val);
        ll cur = a[i] + d * (2*w[i] - val);

        while (cur >= bound) {
            --w[i];
            cur = a[i] + d * (2*w[i] - val);
        }
        if (cur >= bound) return false;
        if (w[i] < 0 || w[i] > val) return false;
        bound = cur;
    }
    return true;
}

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
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

int main() {
    ios :: sync_with_stdio(false);
    GN(n); GN(d);
    FOR(i,1,n) GN(a[i]);
    ll left = 0, right = 1000111000, res = right;
    while (left <= right) {
        ll mid = (left + right) / 2;
        if (check(mid)) res = mid, right = mid - 1;
        else left = mid + 1;
    }
    cout << res << endl;
}
