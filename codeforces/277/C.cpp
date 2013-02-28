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

typedef pair<int,int> Point;
typedef pair<Point,Point> Seg;

const int MN = 400111;

Seg a[MN], b[MN];
int cx[MN], cy[MN], m, n, k, sx, sy;
vector< pair<int,int> > row[MN], col[MN];
int valRow[MN], valCol[MN];

bool check(int a, int b, int c) {
    return a != b && a != c;
}

void init() {
    sx = sy = 0;
    FOR(i,1,k) {
        if (check(a[i].F.F, 0, n)) cx[++sx] = a[i].F.F;
        if (check(a[i].S.F, 0, n)) cx[++sx] = a[i].S.F;

        if (check(a[i].F.S, 0, m)) cy[++sy] = a[i].F.S;
        if (check(a[i].S.S, 0, m)) cy[++sy] = a[i].S.S;
    }

    sort(cx+1, cx+sx+1);
    sort(cy+1, cy+sy+1);
    sx = unique(cx+1, cx+sx+1) - cx - 1;
    sy = unique(cy+1, cy+sy+1) - cy - 1;
    FOR(i,1,max(sx,sy) + 2) {
        row[i].clear();
        col[i].clear();
    }

    FOR(i,1,k) {
        if (a[i].F.F == 0) b[i].F.F = 0;
        else if (a[i].F.F == n) b[i].F.F = sx + 10;
        else b[i].F.F = lower_bound(cx+1, cx+sx+1, a[i].F.F) - cx;
        if (a[i].S.F == 0) b[i].S.F = 0;
        else if (a[i].S.F == n) b[i].S.F = sx + 10;
        else b[i].S.F = lower_bound(cx+1, cx+sx+1, a[i].S.F) - cx;

        if (a[i].F.S == 0) b[i].F.S = 0;
        else if (a[i].F.S == m) b[i].F.S = sy + 10;
        else b[i].F.S = lower_bound(cy+1, cy+sy+1, a[i].F.S) - cy;

        if (a[i].S.S == 0) b[i].S.S = 0;
        else if (a[i].S.S == m) b[i].S.S = sy + 10;
        else b[i].S.S = lower_bound(cy+1, cy+sy+1, a[i].S.S) - cy;

        if (b[i].F.F == b[i].S.F) {
            // cout << "col: " << b[i].F.F << ' ' << min(a[i].F.S, a[i].S.S) << ' ' <<  max(a[i].F.S, a[i].S.S) << endl;
            col[b[i].F.F].PB(MP(min(a[i].F.S, a[i].S.S), max(a[i].F.S, a[i].S.S)));
        }
        else {
            // cout << "row: " << b[i].F.S << ' ' << min(a[i].F.F, a[i].S.F) << ' ' <<  max(a[i].F.F, a[i].S.F) << endl;
            row[b[i].F.S].PB(MP(min(a[i].F.F, a[i].S.F), max(a[i].F.F, a[i].S.F)));
        }
    }
}

void solve() {
    FOR(i,1,sx) {
        int len = 0, last = 0;
        sort(col[i].begin(), col[i].end());
        col[i].PB(MP(m, m));

        if (cx[i] == 0 || cx[i] == n) continue;

        REP(x,col[i].size()) {
            int cur = col[i][x].F;
            if (cur > last) {
                len += cur - last;
            }
            last = max(last, col[i][x].S);
        }

        valCol[i] = len;
    }

    FOR(i,1,sy) {
        int len = 0, last = 0;
        sort(row[i].begin(), row[i].end());
        row[i].PB(MP(n, n));

        if (cy[i] == 0 || cy[i] == m) continue;

        REP(x,row[i].size()) {
            int cur = row[i][x].F;
            if (cur > last) {
                len += cur - last;
            }
            last = max(last, row[i][x].S);
        }

        valRow[i] = len;
    }
}

void print(int need, vector< pair<int,int> > row, int i, bool dir) {
    if (row.size() == 0) {
        if (dir) {
            cout << cx[i] << ' ' << 0 << ' ' << cx[i] << ' ' << need << endl;
        }
        else {
            cout << 0 << ' ' << cy[i] << ' ' << need << ' ' << cy[i] << endl;
        }
        return ;
    }
    int last = 0, len = 0;
    REP(x,row.size()) {
        int cur = row[x].F;
        if (cur > last) {
            len += cur - last;
            if (len >= need) {
                cur -= len - need;

                if (cur >= last) {
                    if (dir) {
                        cout << cx[i] << ' ' << 0 << ' ' << cx[i] << ' ' << cur << endl;
                    }
                    else {
                        cout << 0 << ' ' << cy[i] << ' ' << cur << ' ' << cy[i] << endl;
                    }
                    return ;
                }
            }
        }
        last = max(last, row[x].S);
    }
}

int find(int c[], int n) {
    set<int> s; s.clear();
    FOR(i,1,n) s.insert(c[i]);
    int res = 1;
    while (s.find(res) != s.end()) ++res;
    return res;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        FOR(i,1,k) {
            scanf("%d%d%d%d", &a[i].F.F, &a[i].F.S, &a[i].S.F, &a[i].S.S);
        }
        init();
        solve();

        int sum = 0;
        FOR(i,1,sx) sum ^= valCol[i];
        if ((n - 1 - sx) % 2 == 1) {
            sum ^= m;
            valCol[++sx] = m;
            cx[sx] = find(cx, sx-1);
            col[sx].PB(MP(m,m));
        }
        else {
            if (sx < n-1) {
                valCol[++sx] = m;
                cx[sx] = find(cx, sx-1);

                valCol[++sx] = m;
                cx[sx] = find(cx, sx-1);
            }
        }
        FOR(i,1,sy) sum ^= valRow[i];
        if ((m - 1 - sy) % 2 == 1) {
            sum ^= n;
            valRow[++sy] = n;
            cy[sy] = find(cy, sy-1);
        }
        else {
            if (sy < m-1) {
                valRow[++sy] = n;
                cy[sy] = find(cy, sy-1);
                row[sy].PB(MP(n,n));
                valRow[++sy] = n;
                cy[sy] = find(cy, sy-1);
            }
        }

        // PR(cx, sx);
        // PR(cy, sy);

        // PR(valCol, sx);
        // PR(valRow, sy);

        if (sum) {
            puts("FIRST");
            bool ok = false;
            FOR(i,1,sx) {
                if ((sum ^ valCol[i]) < valCol[i]) {
                    print(valCol[i] - (sum ^ valCol[i]), col[i], i, true);
                    ok = true;
                    break;
                }
            }
            if (ok) continue;
            // DEBUG(sum);
            FOR(i,1,sy) {
                if ((sum ^ valRow[i]) < valRow[i]) {
                    print(valRow[i] - (sum ^ valRow[i]), row[i], i, false);
                    ok = true;
                    break;
                }
            }
        }
        else {
            puts("SECOND");
        }
        puts("");
    }
    return 0;
}
