#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

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

const long double PI = acos((long double) -1.0);
const int MN = 200111;

int a[MN], n, k;
long long sum[MN], l[MN], r[MN];
int savel[MN], saver[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) sum[i] = sum[i-1] + a[i];

        FOR(i,k,n) {
            long long now = sum[i] - sum[i-k];
            if (now > l[i-1]) {
                l[i] = now;
                savel[i] = i - k + 1;
            }
            else {
                l[i] = l[i-1];
                savel[i] = savel[i-1];
            }
        }
        FORD(i,n-k+1,1) {
            long long now = sum[i+k-1] - sum[i-1];
            if (now >= r[i+1]) {
                r[i] = now;
                saver[i] = i;
            }
            else {
                r[i] = r[i+1];
                saver[i] = saver[i+1];
            }
        }

        long long res = 0;
        int save1, save2;
        FOR(i,k,n-k) {
            long long now = l[i] + r[i+1];
            if (now > res) {
                res = now;
                save1 = savel[i], save2 = saver[i+1];
            }
        }
        // cout << res << endl;
        cout << save1 << ' ' << save2 << endl;
    }
    return 0;
}
