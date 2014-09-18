#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 500111;

#define next next_

int n, a[MN], next[MN], f[MN], g[MN], tr[MN];
map<int,int> cur;
vector<int> it[MN * 4];

void init() {
    cur.clear();
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

#define left { it[i].push_back(it[CT(i)][x++]); }
#define right { it[i].push_back(it[CP(i)][y++]); }

void build(int i, int l, int r) {
    it[i].clear();

    if (l == r) {
        it[i].push_back(next[l]);
        return ;
    }

    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    int x = 0, y = 0;
    REP(turn,r-l+1) {
        if (x == it[CT(i)].size()) right
        else if (y == it[CP(i)].size()) left
        else {
            if (it[CT(i)][x] < it[CP(i)][y]) left
            else right;
        }
    }
}

int get(int i, int l, int r, int u, int v, int x) {
    if (v < l || r < u) return n+1;
    if (u <= l && r <= v) {
        if (it[i].back() <= x) return n+1;
        else return *upper_bound(it[i].begin(), it[i].end(), x);
    }

    int mid = (l + r) >> 1;
    return min(get(CT(i), l, mid, u, v, x), get(CP(i), mid+1, r, u, v, x));
}

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

int main() {
    REP(test,1) {
        GN(n);
        init();
        FOR(i,1,n) GN(a[i]);

        FORD(i,n,1) {
            if (cur.count(a[i])) {
                next[i] = cur[a[i]];
            } else {
                next[i] = n + 1;
            }
            cur[a[i]] = i;
        }
        // PR(next, n);

        build(1, 1, n);

        FOR(i,1,n) {
            if (next[i] > n) f[i] = n + 1;
            else {
                f[i] = get(1, 1, n, i+1, next[i] - 1, next[i]);

                int u = next[i];
                if (u <= n) {
                    int v = next[u];
                    if (v <= n) {
                        int w = next[v];
                        f[i] = min(f[i], w);
                    }
                }
            }
        }
        // PR(f, n);

        g[n+1] = 0;
        FORD(i,n,1) {
            g[i] = g[i+1];
            tr[i] = 0;

            if (f[i] <= n) {
                int cur = g[f[i] + 1] + 1;
                if (cur > g[i]) {
                    tr[i] = 1;
                    g[i] = cur;
                }
            }
        }
        // PR(g, n);
        printf("%d\n", g[1] * 4);
        int i = 1;
        while (i <= n) {
            if (tr[i]) {
                printf("%d %d %d %d ", a[i], a[f[i]], a[i], a[f[i]]);
                i = f[i] + 1;
            }
            else ++i;
        }
        puts("");
    }
    return 0;
}
