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

pair<int, pair<int,int> > e[100111];
int m;
map<string,int> id;
int lab[111];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    }
    else {
        lab[u] = v;
        lab[v] = x;
    }
}

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m) {
        id.clear();
        id["Park"] = 1;
        int n = 1;

        FOR(i,1,m) {
            string a, b; cin >> a >> b;
            int c; cin >> c;
            if (id.find(a) == id.end()) id[a] = ++n;
            if (id.find(b) == id.end()) id[b] = ++n;

            e[i] = make_pair(c, make_pair(id[a], id[b]));
        }
        sort(e+1, e+m+1);

        int res = 1000111000;
        int gh; cin >> gh;

        REP(mask,TWO(n-1)) if (__builtin_popcount(mask) <= gh) {
            int cur = 0, cnt = 0;
            memset(lab, -1, sizeof lab);
            FOR(i,1,m) {
                int u = e[i].second.first, v = e[i].second.second;
                if (min(u, v) == 1 && !CONTAIN(mask,max(u, v) - 2)) continue;

                u = getRoot(u), v = getRoot(v);
                if (u == v) continue;

                cur += e[i].first;
                merge(u, v);
                ++cnt; if (cnt == n-1) break;
            }
            if (cnt == n-1) res = min(res, cur);
        }
        cout << "Total miles driven: " << res << endl;
    }
    return 0;
}