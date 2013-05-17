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

const long double PI = acos((long double) -1.0);
const int MN = 1000111;

int n, m;
int cnta[33], cntb[33];

void insert(int u, int lb = 0, int ub = 30) {
    for(int i = lb; i < ub; ++i)
        if (u & (1<<i))
            ++cnta[i];
}

int main() {
    while (scanf("%d%d", &m, &n) == 2) {
        int a;
        FOR(i,1,m) {
            scanf("%d", &a);
            insert(a);
        }
        FOR(j,1,n) {
            int t; scanf("%d", &t);
            cntb[t]++;
        }
        // PR0(cnta, 30);
        // PR0(cntb, 30);
        int res = 0;
        REP(i,30) while (cntb[i]) {
            bool ok = false;
            int savej = -1;
            for(int j = i; j < 30; ++j)
                if (cnta[j]) {
                    ok = true;
                    savej = j;
                    break;
                }
            if (!ok) break;

            --cnta[savej];
            --cntb[i];
            int u = (1<<savej) - (1<<i);
            if (u) insert(u,i,savej);
            ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}
