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
int n, m, s, f;
pair<int,int> a[MN];

bool bad(int t, int s) {
    if (s >= a[t].first && s <= a[t].second) return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> s >> f) {
        memset(a, 0, sizeof a);

        FOR(i,1,m) {
            int l, r, t; cin >> t >> l >> r;
            if (t < 200111) {
                a[t] = make_pair(l, r);
            }
        }
        FOR(t,1,200111) {
            if (s == f) break;
            if (s < f) {
                if (bad(t, s) || bad(t, s+1)) putchar('X');
                else {
                    ++s;
                    putchar('R');
                }
            }
            else {
                if (bad(t, s) || bad(t, s-1)) putchar('X');
                else {
                    --s;
                    putchar('L');
                }
            }
        }
        puts("");
    }
    return 0;
}
