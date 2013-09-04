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

const int MN = 1011;
int a[MN], n, x[11];
vector< pair<int,int> > res;

void solve(int x, int y, int z) {
    if (a[y] < a[x]) swap(x, y);
    if (a[z] < a[x]) swap(x, z);
    if (a[z] < a[y]) swap(y, z);

    if (a[x] == 0) return ;

    int mv = a[y] / a[x];
    REP(bit,30) {
        if ((1<<bit) > mv) break;
        if (mv & (1<<bit)) {
            res.push_back(make_pair(x, y));
            a[y] -= a[x];
            a[x] += a[x];
        }
        else {
            res.push_back(make_pair(x, z));
            a[z] -= a[x];
            a[x] += a[x];
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        res.clear();
        FOR(i,1,n) cin >> a[i];

        int cnt = 0;
        FOR(i,1,n) if (a[i]) {
            ++cnt;
            x[cnt] = i;
            if (cnt == 3) break;
        }
        if (cnt < 2) {
            puts("-1\n");
            continue;
        }
        while (cnt == 3) {
            solve(x[1], x[2], x[3]);
            cnt = 0;
            FOR(i,1,n) if (a[i]) {
                ++cnt;
                x[cnt] = i;
                if (cnt == 3) break;
            }
        }

        printf("%d\n", res.size());
        REP(i,res.size()) printf("%d %d\n", res[i].first, res[i].second);
        puts("");
    }
    return 0;
}
