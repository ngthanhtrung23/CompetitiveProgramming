#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

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
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
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

int m, n;
char a[33][33];
long long f[33][33], nTime[33][33];
long long total[333];
pair<int,int> st[66][1011];
int top[66];

int main() {
    freopen("kthpath.in", "r", stdin);
    freopen("kthpath.out", "w", stdout);

    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        long long k; cin >> k;

        memset(f, 0, sizeof f);

        FORD(i,m,1) FORD(j,n,1) {
            if (i == m && j == n) f[i][j] = 1;
            else f[i][j] = f[i+1][j] + f[i][j+1];
        }
        if (k > f[1][1]) k = f[1][1];

        string res = "";

        memset(top, 0, sizeof top);
        memset(nTime, 0, sizeof nTime);
        top[0] = 1; st[0][1] = MP(1,1);
        nTime[1][1] = 1;

        FOR(turn,1,m+n-1) {
            memset(total, 0, sizeof total);

            FOR(i,1,top[turn-1]) {
                int u = st[turn-1][i].first, v = st[turn-1][i].second;
                total[a[u][v]] += f[u][v] * nTime[u][v];
            }

            long long now = 0;
            char need = 'z';
            FOR(c,'a','z') {
                if (total[c] >= k) {
                    need = c;
                    break;
                }
                else k -= total[c];
            }
            cout << need;

            FOR(i,1,top[turn-1]) {
                int u = st[turn-1][i].first, v = st[turn-1][i].second;
                if (a[u][v] != need) continue;

                if (u < m) {
                    ++top[turn];
                    st[turn][top[turn]] = MP(u+1, v);

                    nTime[u+1][v] += nTime[u][v];
                }

                if (v < n) {
                    ++top[turn];
                    st[turn][top[turn]] = MP(u, v+1);

                    nTime[u][v+1] += nTime[u][v];
                }
            }
            sort(st[turn]+1, st[turn] + top[turn] + 1);
            top[turn] = unique(st[turn] + 1, st[turn] + top[turn] + 1) - st[turn] - 1;
        } // for turn
        cout << endl;
    } // while read input
    return 0;
}
