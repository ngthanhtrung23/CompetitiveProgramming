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

const int MN = 1011;
const int MOD = (int) (1e9 + 7);

int m, n;
char s[MN][MN];
int a[MN][MN];

long long f[MN], cnt[MN][MN];

void solve() {
    memset(cnt, 0, sizeof cnt);
    memset(f, 0, sizeof f);

    f[0] = 1;
    FOR(j,1,n) {
        // All vertical
        bool check = m % 2 == 0;
        FOR(i,1,m) if (a[i][j] == 2) check = false;

        if (check) f[j] = f[j-1]; // Put all vertical at column j
        else f[j] = 0;

        if (j >= 2) {
            cnt[m+1][j] = 1;
            FORD(i,m,1) {
                cnt[i][j] = 0;
                if (a[i][j] != 1 && a[i][j-1] != 1) {
                    cnt[i][j] = (cnt[i][j] + cnt[i+1][j]) % MOD;
                }
                if (i <= m-1 
                        && a[i  ][j] != 2 && a[i  ][j-1] != 2 
                        && a[i+1][j] != 2 && a[i+1][j-1] != 2) {
                    cnt[i][j] = (cnt[i][j] + cnt[i+2][j]) % MOD;
                }
            }

            FOR(i,1,m) { // First horizontal at i
                if ((i-1) % 2 == 0 && a[i][j] != 1 && a[i][j-1] != 1) {
                    f[j] = (f[j] + f[j-2] * cnt[i+1][j]) % MOD;
                }
                if (a[i][j] == 2 || a[i][j-1] == 2) break;
            }
        }
    }
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,4*m+1) {
            scanf("%s\n", &s[i][1]);
        }
        for(int i = 1, r = 2; i <= m; ++i, r += 4) {
            for(int j = 1, c = 2; j <= n; ++j, c += 4) {
                int cnt = 0;
                FOR(u,r,r+2) FOR(v,c,c+2)
                    if (s[u][v] == 'O')
                        ++cnt;
                if (cnt == 0 || cnt == 1 || cnt == 4 || cnt == 5) {
                    a[i][j] = 3;
                }
                else if (cnt == 2 || cnt == 3) {
                    if (s[r][c] == 'O')
                        a[i][j] = 2;
                    else a[i][j] = 1;
                }
                else {
                    if (s[r+1][c] == 'O')
                        a[i][j] = 1;
                    else a[i][j] = 2;
                }
            }
        }
        // FOR(i,1,m) { PR(a[i], n); }

        solve();
        cout << f[n] << endl;
    }
    return 0;
}
