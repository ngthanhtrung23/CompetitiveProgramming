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

int c[211][211];
int eu[211*211], ev[211*211], ec[211*211];
int n, m;

pair<int, int> a[211];
int nA;

bool check(int val) {
    FOR(i,1,m) {
        int u = eu[i], v = ev[i];

        nA = 0;
        bool check1 = true, check2 = true;
        FOR(x,1,n) {
            if (val >= c[v][x] + ec[i]) continue;
            if (val >= c[u][x] + ec[i]) continue;

            int left = val - c[u][x];
            if (left < 0) check1 = false;

            int right = val - c[v][x];
            if (right < 0) check2 = false;

            a[++nA] = make_pair(left, ec[i] - right);
        }

        // FOR(i,1,nA) cout << a[i].first << ' ' << a[i].second << endl;

        if (check1 || check2) return true;

        sort(a+1, a+nA+1);
        int reach = 0;
        FOR(i,1,nA) {
            if (a[i].first >= reach) return true;
            reach = max(reach, a[i].second);
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) FOR(j,1,n) if (i == j) c[i][j] = 0; else c[i][j] = 1000211000;
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            eu[i] = u; ev[i] = v;
            scanf("%d", &c[u][v]);
            c[u][v] *= 2;

            c[v][u] = c[u][v];

            ec[i] = c[u][v];
        }
        FOR(k,1,n) 
            FOR(i,1,n) FOR(j,1,n)
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        int l = 0, r = 1000111000, res = r;
        // DEBUG(check(0.5)); continue;

        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << (fixed) << setprecision(14) << res / 2.0 << endl;
    }
    return 0;
}
