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

int n, cx[MN], cy[MN], valx[MN], valy[MN], sx, sy;
pair<int,int> a[MN];

vector<int> it[MN * 3];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    it[i].clear();
    if (l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
}

void add(int i, int l, int r, int u, int k) {
    if (u < l || u > r) return ;
    it[i].push_back(cy[k]);
    if (l == r) return ;

    int mid = (l + r) >> 1;
    add(CT(i), l, mid, u, k);
    add(CP(i), mid+1, r, u, k);
}

void update(int i, int l, int r) {
    sort(it[i].begin(), it[i].end());
    if (l == r) return ;

    int mid = (l + r) >> 1;
    update(CT(i), l, mid);
    update(CP(i), mid+1, r);
}

int get(int i, int l, int r, int x, int y) {
    if (x < l) return 0;
    if (x >= r) {
        if (!it[i].size()) return 0;
        if (cy[y] >= it[i][it[i].size()-1]) return it[i].size();
        else return upper_bound(it[i].begin(), it[i].end(), cy[y]) - it[i].begin();
    }

    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, x, y) + get(CP(i), mid+1, r, x, y);
}

void RR() {
    sort(cx+1, cx+n+1);
    sx = unique(cx+1, cx+n+1) - cx - 1;
    FOR(i,1,n) a[i].F = lower_bound(cx+1, cx+sx+1, a[i].F) - cx;

    sort(cy+1, cy+n+1);
    sy = unique(cy+1, cy+n+1) - cy - 1;
    FOR(i,1,n) a[i].S = lower_bound(cy+1, cy+sy+1, a[i].S) - cy;

    // PR(cx, sx);
    // PR(cy, sy);
}

bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
    if (a.S != b.S) return a.S < b.S;
    return a.F < b.F;
}

void init() {
    memset(valx, 0, sizeof valx);
    memset(valy, 0, sizeof valy);

    sort(a+1, a+n+1);
    int j = 0, now = 0;
    FOR(i,1,sx) {
        while (j < n && a[j+1].F <= i) {
            ++j;
            ++now;
        }

        // cout << i << ' ' << now << endl;

        valx[now] = i;
    }
    // PR(valx, n);

    sort(a+1, a+n+1, cmp);
    j = 0; now = 0;
    FOR(i,1,sy) {
        while (j < n && a[j+1].S <= i) {
            ++j;
            ++now;
        }

        valy[now] = i;
    }
    // PR(valy, n);
}

int need[11];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d%d", &a[i].F, &a[i].S);
            cx[i] = a[i].F;
            cy[i] = a[i].S;
        }
        RR();
        init();

        FOR(i,1,9) scanf("%d", &need[i]);

        bool ok = false;

        build(1, 1, sx);
        FOR(i,1,n) add(1, 1, sx, a[i].F, a[i].S);
        update(1, 1, sx);

        cy[sy+1] = cy[sy] + 1;

        sort(need+1, need+10);

        do {
            int x1 = valx[need[1] + need[4] + need[7]];
            int x2 = valx[need[1] + need[4] + need[7]
                        + need[2] + need[5] + need[8]];
            if (!x1 || !x2) continue;

            int y1 = valy[need[1] + need[2] + need[3]];
            int y2 = valy[need[1] + need[2] + need[3]
                        + need[4] + need[5] + need[6]];
            if (!y1 || !y2) continue;

            if (get(1, 1, sx, x1, y1) != need[1]) continue;
            if (get(1, 1, sx, x2, y1) != need[1] + need[2]) continue;
            if (get(1, 1, sx, x1, y2) != need[1] + need[4]) continue;
            if (get(1, 1, sx, x2, y2) != need[1] + need[2] + need[4] + need[5]) continue;
            if (get(1, 1, sx, x1, sy+1) != need[1] + need[4] + need[7]) continue;

            printf("%.3lf %.3lf\n%.3lf %.3lf\n", 
                cx[x1] + (double) 0.5, cx[x2] + (double) 0.5,
                cy[y1] + (double) 0.5, cy[y2] + (double) 0.5);
            ok = true;
            break;
        } while (next_permutation(need+1, need+10));

        if (!ok) puts("-1");
    }
    return 0;
}
