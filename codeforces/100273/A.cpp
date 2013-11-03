#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

#define EPS 1e-10

int Lmate[111], Rmate[111];
double cost[111][111];

typedef double VD[111];
typedef double VVD[111][111];
typedef int VI[111];

double MinCostMatching(int n) {
    VD u = {0};
    VD v = {0};
    REP (i, n) {
        u[i] = cost[i][0];
        FOR (j, 1, n-1) u[i] = min(u[i], cost[i][j]);
    }
    REP (j, n) {
        v[j] = cost[0][j] - u[0];
        FOR (i, 1, n-1) v[j] = min(v[j], cost[i][j] - u[i]);
    }
    REP (i, n) Lmate[i] = Rmate[i] = -1;
    int mated = 0;
    REP (i, n) REP (j, n) {
        if (Rmate[j] != -1) continue;
        if (fabs(cost[i][j] - u[i] - v[j]) < EPS) {
            Lmate[i] = j;
            Rmate[j] = i;
            mated++;
            break;
        }
    }
    VD dist = {0};
    VI dad = {0};
    VI seen = {0};
    while (mated < n) {
        int s = 0;
        while (Lmate[s] != -1) s++;
        fill(dad, dad + n, -1);
        fill(seen, seen + n, 0);
        REP (k, n) dist[k] = cost[s][k] - u[s] - v[k];
        int j = 0;
        while (true) {
            j = -1;
            REP (k, n) {
                if (seen[k]) continue;
                if (j == -1 || dist[k] < dist[j]) j = k;
            }
            seen[j] = 1;
            if (Rmate[j] == -1) break;
            const int i = Rmate[j];
            REP (k, n) {
                if (seen[k]) continue;
                double new_dist = dist[j] + cost[i][k] - u[i] - v[k];
                if (dist[k] > new_dist) {
                    dist[k] = new_dist;
                    dad[k] = j;
                }
            }
        }
        REP (k, n) {
            if (k == j || !seen[k]) continue;
            const int i = Rmate[k];
            v[k] += dist[k] - dist[j];
            u[i] -= dist[k] - dist[j];
        }
        u[s] += dist[j];
        while (dad[j] >= 0) {
            const int d = dad[j];
            Rmate[j] = Rmate[d];
            Lmate[Rmate[j]] = j;
            j = d;
        }
        Rmate[j] = s;
        Lmate[s] = j;
        mated++;
    }
    double value = 0;
    REP (i, n) value += cost[i][Lmate[i]];
    return value;
}

int n;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    double len() { return sqrt(x*x + y*y); }
} ant[111], place[111];

int main() {
    freopen("ants.in", "r", stdin);
    freopen("ants.out", "w", stdout);

    ios :: sync_with_stdio(false);
    while (cin >> n) {
        REP(i,n) cin >> ant[i].x >> ant[i].y;
        REP(i,n) cin >> place[i].x >> place[i].y;

        REP(i,n) REP(j,n) cost[i][j] = (ant[i] - place[j]).len();
        MinCostMatching(n);
        REP(i,n) cout << Lmate[i] + 1 << endl;
    }
    return 0;
}
