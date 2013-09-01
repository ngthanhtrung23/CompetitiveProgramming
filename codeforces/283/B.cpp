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

const int MN = 200111;

int n, a[MN], visited[2][MN], turn;
long long f[2][MN];

long long dfs(int x, int dir) {
    visited[dir][x] = turn;
    long long res = 0;
    int savex = x;
    if (dir == 0) {
        res = a[x];
        x += a[x];
    }
    else {
        res = a[x];
        x -= a[x];
    }

    if (x == 1) return f[dir][savex] = -1;

    if (x < 1 || x > n) return f[dir][savex] = res;
    if (visited[1-dir][x] == turn) return f[dir][savex] = -1;
    else if (visited[1-dir][x]) {
        if (f[1-dir][x] < 0) return f[dir][savex] = -1;
        return f[dir][savex] = res + f[1-dir][x];
    }

    long long t = dfs(x, 1-dir);
    if (t < 0) return f[dir][savex] = -1;
    return f[dir][savex] = t + res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,2,n) cin >> a[i];

        memset(visited, false, sizeof visited);
        memset(f, -1, sizeof f);

        FOR(i,2,n) REP(dir,2)
        if (!visited[dir][i]) {
            ++turn;
            dfs(i, dir);
        }
        // PR(f[0], n);
        // PR(f[1], n);

        FOR(i,1,n-1) {
            long long t = f[1][i+1];
            if (t < 0) cout << -1 << "\n";
            else cout << i+t << "\n";
        }
    }
    return 0;
}
