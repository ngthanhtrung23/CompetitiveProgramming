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
const int MN = 100111;

struct Node {
    int sum, minRight, maxRight;
} it[MN * 3];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].sum = val;
        it[i].minRight = it[i].maxRight = it[i].sum;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);

    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
    it[i].minRight = min(it[CP(i)].minRight, it[CP(i)].sum + it[CT(i)].minRight);
    it[i].maxRight = max(it[CP(i)].maxRight, it[CP(i)].sum + it[CT(i)].maxRight);
}

int n;

int main() {
    freopen("stones.in", "r", stdin);
    freopen("stones.out", "w", stdout);
    while (scanf("%d", &n) == 1) {
        memset(it, 0, sizeof it);
        
        FOR(i,1,n) {
            int u, side; scanf("%d%d", &u, &side);
            if (side == 1) update(1, 1, n, u, -1);
            else update(1, 1, n, u, 1);

            if (it[1].minRight >= 0) puts("<");
            else if (it[1].maxRight <= 0) puts(">");
            else puts("?");
        }
    }
    return 0;
}
