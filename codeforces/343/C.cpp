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

const int MN = 100111;
int n, m;
long long a[MN], b[MN];

bool check(long long val) {
    int j = 0;
    for(int i = 1; i <= n; ++i) {
        if (b[j+1] <= a[i]) {
            long long d = a[i] - b[j+1];
            if (val < d) return false;

            long long gh = a[i] + max((val - d) >> 1, val - d - d);

            int l = j+1, r = m, res = j+1;

            while (l <= r) {
                int mid = (l + r) >> 1;
                if (b[mid] <= gh)
                    res = mid, l = mid + 1;
                else r = mid - 1;
            }
            j = res;
        }
        else {
            long long gh = a[i] + val;
            int l = j, r = m, res = j;

            while (l <= r) {
                int mid = (l + r) >> 1;
                if (b[mid] <= gh)
                    res = mid, l = mid + 1;
                else r = mid - 1;
            }
            j = res;
        }
        if (j >= m) return true;
    }
    return j >= m;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,m) cin >> b[i];

        long long l = 0, r = 20001110001LL, res = r;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
