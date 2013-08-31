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

int n, qu[111], first, last;
pair<int,int> a[111];
bool visited[111];

bool bfs(int start, int target) {
    memset(visited, false, sizeof visited);
    qu[first = last = 1] = start;
    visited[start] = true;

    while (first <= last) {
        int u = qu[first++];
        if (u == target) return true;
        FOR(i,1,n) if (!visited[i]) {
            if ((a[i].first < a[u].first && a[u].first < a[i].second)
                    || (a[i].first < a[u].second && a[u].second < a[i].second)) {
                qu[++last] = i;
                visited[i] = true;
            }
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    int q;
    while (cin >> q) {
        n = 0;
        while (q--) {
            int type, u, v;
            cin >> type >> u >> v;
            if (type == 1) {
                a[++n] = make_pair(u, v);
            }
            else {
                if (bfs(u, v)) puts("YES"); else puts("NO");
            }
        }
    }
    return 0;
}
