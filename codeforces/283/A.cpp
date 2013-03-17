#define _GLIBCXX_DEBUG
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
const int MN = 200111;

int n, sz;
int it[MN * 6];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i] += val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, v, val);
    update(CP(i), mid+1, r, u, v, val);
}

int get(int i, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) {
        return it[i];
    }

    if (it[i]) {
        it[CT(i)] += it[i];
        it[CP(i)] += it[i];
        it[i] = 0;
    }
    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, u) + get(CP(i), mid+1, r, u);
}

int main() {
    while (scanf("%d", &n) == 1) {
        sz = 1; memset(it, 0, sizeof it);

        long double sum = 0;

        FOR(nn,1,n) {
            int q; scanf("%d", &q);
            if (q == 1) {
                int x, val;
                scanf("%d%d", &x, &val);
                update(1, 1, n+1, 1, x, val);

                sum += x * val;
            }
            else if (q == 2) {
                ++sz;
                int val;
                scanf("%d", &val);
                update(1, 1, n+1, sz, sz, val);

                sum += val;
            }
            else if (q == 3) {
                int t = get(1, 1, n+1, sz);
                update(1, 1, n+1, sz, sz, -t);
                --sz;
                sum -= t;
            }

            printf("%.9lf\n", (double) (sum / sz));
        }
    }
    return 0;
}
