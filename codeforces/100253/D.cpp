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

const int MN = 1011;
int out[MN];

int query(vector<int> x) {
    printf("%d\n", x.size());
    REP(i,x.size()) printf("%d ", x[i]);
    puts("");
    fflush(stdout);

    int res; scanf("%d", &res);
    return res;
}

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        int n; scanf("%d", &n);
        vector<int> good, bad;
        FOR(i,1,n) {
            vector<int> cur; cur.push_back(i);
            int res = query(cur);

            if (res == 0) bad.push_back(i);
            else good.push_back(i);
        }

        REP(i,good.size()) {
            int u = good[i];

            bad.push_back(u);
            if (query(bad) == 0) out[u] = 3;
            else out[u] = 1;
            bad.pop_back();
        }

        REP(i,bad.size()) {
            int u = bad[i];

            good.push_back(u);
            if (query(good) == good.size()) out[u] = 3;
            else out[u] = 2;
            good.pop_back();
        }

        puts("-1");
        FOR(i,1,n) {
            printf("%d ", out[i]);
        }
        puts("");
        fflush(stdout);
    }
    return 0;
}
