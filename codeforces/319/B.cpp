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

const int MN = 100111;

int n, a[MN], next[MN], prev[MN];
queue<int> qu;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        while (!qu.empty()) qu.pop();

        a[n+1] = 1000111000;
        FOR(i,1,n) {
            cin >> a[i];
            if (i < n) {
                qu.push(i);
            }
        }
        FOR(i,0,n) next[i] = i+1;
        FOR(i,1,n+1) prev[i] = i-1;

        int last = n + 1, res = 0;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            if (a[u] > a[next[u]]) {
                int b = next[u];
                int a = prev[b];
                int c = next[b];

                next[a] = c;
                prev[c] = a;

                if (u == a) qu.push(u);

                if (u <= last) ++res;
                last = u;
            }
        }
        cout << res << endl;
    }
    return 0;
}
