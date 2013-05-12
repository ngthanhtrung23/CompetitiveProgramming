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

const int MN = 2000111;

int n, m;
int f[MN], tr[MN], used[MN];
vector<int> ke[MN];
bool need[MN];
pair<int,int> seg[MN];
int color[MN];
int it[MN * 3];

void init() {
    FOR(i,1,n) ke[i].clear();
    FOR(i,1,n) f[i] = MN, tr[i] = -1, used[i] = 0;
    memset(need, false, sizeof need);
    memset(color, 0, sizeof color);
    memset(it, -1, sizeof it);
}

void paint() {
    FOR(i,1,m) {
        color[seg[i].F]++;
        color[seg[i].S + 1]--;
    }
    FOR(i,1,n) color[i] += color[i-1];
    // PR(color, n);
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return -1;
    if (u <= l && r <= v) return it[i];
    int mid = (l + r) >> 1;

    int x = get(CT(i), l, mid, u, v);
    int y = get(CP(i), mid+1, r, u, v);

    if (x < 0) return y;
    else if (y < 0) return x;
    else if (f[x] < f[y]) return x;
    else return y;
}

void update(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = u;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u);
    update(CP(i), mid+1, r, u);

    if (it[i] < 0 || f[u] < f[it[i]])
        it[i] = u;
}

void solve() {
    f[1] = 0; update(1, 1, n, 1);

    FOR(i,2,n) {
        if (!color[i]) f[i] = f[i-1], tr[i] = i-1, used[i] = 0;
        else {
            f[i] = 1000111; tr[i] = -1;
            REP(t,ke[i].size()) {
                int seg_id = ke[i][t];
                int j = get(1, 1, n, seg[seg_id].F-1, i-1);
                if (j >= 0 && f[j] + 1 < f[i]) {
                    f[i] = f[j] + 1;
                    tr[i] = j;
                    used[i] = seg_id;
                }
            }
        }
        update(1, 1, n, i);
    }
    // PR(color, n);
    // PR(f, n);
    // PR(tr, n);
    // PR(used, n);
    int v = n;
    while (v > 0) {
        if (used[v]) need[used[v]] = true;
        v = tr[v];
    }
    printf("%d\n", m - f[n]);
    FOR(i,1,m) if (!need[i]) printf("%d ", i);
    puts("");
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        ++n;
        FOR(i,1,m) {
            int u, len; scanf("%d%d", &u, &len);
            int v = u + len - 1;
            ++u; ++v;
            ke[v].push_back(i);
            seg[i] = MP(u, v);
        }
        paint();
        solve();
    }
    return 0;
}
