#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
const int BLOCK = 511;

int blockId[MN], a[MN], lastInBlock[MN], cntBlock[MN];
int n, q;

pair<int,int> get(int i) {
    int to = i + a[i];
    if (to > n) return make_pair(i, 0);
    else if (blockId[to] != blockId[i]) return make_pair(i, 0);
    else return make_pair(lastInBlock[to], cntBlock[to] + 1);
}

void init() {
    FOR(i,1,n) blockId[i] = i / BLOCK;
    FORD(i,n,1) {
        auto t = get(i);
        lastInBlock[i] = t.first;
        cntBlock[i] = t.second;
    }
}

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    GN(n); GN(q);
    FOR(i,1,n) GN(a[i]);
    init();
    while (q--) {
        int typ; GN(typ);
        if (typ == 0) {
            int u, val; GN(u); GN(val);
            int b = blockId[u];
            a[u] = val;
            FORD(i,u,1) {
                if (blockId[i] != b) break;
                auto t = get(i);
                lastInBlock[i] = t.first;
                cntBlock[i] = t.second;
            }
        }
        else {
            int u; GN(u);
            int res = 0;
            while (true) {
                // we go to last position in u 's block
                res += cntBlock[u];
                u = lastInBlock[u];

                // from here we try to go to next block
                int to = u + a[u];
                ++res;
                if (to > n) break;

                u = to;
            }
            printf("%d %d\n", u, res);
        }
    }
}
