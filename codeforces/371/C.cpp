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

long long need[3], has[3], price[3], money;
string s;

bool check(long long val) {
    long long sum = 0;
    REP(t,3) {
        long long buy = max(0LL, need[t] * val - has[t]);
        sum += buy * price[t];
    }
    return sum <= money;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        memset(need, 0, sizeof need);
        REP(i,s.length()) {
            if (s[i] == 'B') ++need[0];
            if (s[i] == 'S') ++need[1];
            if (s[i] == 'C') ++need[2];
        }
        REP(i,3) cin >> has[i];
        REP(i,3) cin >> price[i];
        cin >> money;

        long long l = 0, r = 1000111000111LL, res = 0;

        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        cout << res << endl;
    }
    return 0;
}