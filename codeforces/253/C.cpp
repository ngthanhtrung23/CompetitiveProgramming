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

int n, a[111];
int d[111][100111];

pair<int,int> qu[111*100111], start, target;
int first, last;

void add(pair<int,int> u, int x) {
    if (d[u.F][u.S] >= 0) return ;

    d[u.F][u.S] = x;
    qu[++last] = u;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        scanf("%d%d", &start.F, &start.S);
        scanf("%d%d", &target.F, &target.S);

        first = last = 1;
        qu[1] = start;

        memset(d, -1, sizeof d);
        d[start.F][start.S] = 0;

        while (first <= last) {
            pair<int,int> u = qu[first++];
            int l = d[u.F][u.S];

            if (u.F < n) add(MP(u.F+1, min(u.S, a[u.F+1]+1)), l + 1);
            if (u.F > 1) add(MP(u.F-1, min(u.S, a[u.F-1]+1)), l + 1);

            if (u.S < a[u.F]+1) add(MP(u.F, u.S + 1), l+1);
            if (u.S > 1) add(MP(u.F, u.S - 1), l+1);
        }

        cout << d[target.F][target.S] << endl;
    }
    return 0;
}
