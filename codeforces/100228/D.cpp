#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    double sqlen() { return x*x + y*y; }
} a[22];

int color[22], n;
vector<int> ke[22];

bool can(int u, int c) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (color[v] && color[v] == c) return false;
    }
    return true;
}

bool attempt(int i, int gh) {
    if (i > n) {
        return true;
    }

    FOR(c,1,gh) if (can(i, c)) {
        color[i] = c;
        bool tmp = attempt(i+1, gh);
        if (tmp) return true;
    }
    return false;
}

bool check(int res) {
    memset(color, 0, sizeof color);
    return attempt(1, res);
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n && n) {
        FOR(i,1,n) cin >> a[i].x >> a[i].y;
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,n) FOR(j,i+1,n) if ((a[i] - a[j]).sqlen() <= 400 + 1e-6) {
            ke[i].push_back(j);
            ke[j].push_back(i);
        }
        bool ok = false;
        int best = 4;
        FOR(res,1,3) if (check(res)) {
            best = res;
            break;
        }
        cout << "The towers in case " << ++test << " can be covered in " << best << " frequencies." << endl;
    }
    return 0;
}