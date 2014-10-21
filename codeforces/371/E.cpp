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

pair<long long,int> x[MN];
long long sum[MN];
int n, k;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> x[i].first;
            x[i].second = i;
        }
        sort(x+1, x+n+1);
        cin >> k;
        FOR(i,1,n) sum[i] = sum[i-1] + x[i].first;

        long long cur = 0;
        FOR(i,1,k) cur += x[i].first * (2*i-k-1);

        long long best = cur;
        int save = 1;

        FOR(i,k+1,n) {
            cur -= x[i-k].first * (2-k-1LL);
            cur -= (sum[i-1]-sum[i-k]) * 2LL;
            cur += (2*k - k - 1) * x[i].first;

            if (best > cur) {
                best = cur;
                save = i - k + 1;
            }
        }

        // cout << best << endl;
        FOR(i,save,save+k-1) cout << x[i].second << ' '; cout << endl;
    }
    return 0;
}