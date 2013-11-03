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

const int MN = 211;
struct Writing {
    int nPoint, nStroke;
    int c[MN][MN];

    pair<int,int> pos[MN];
} first, cur;

map< pair<int,int>, int> id;
pair< pair<int,int>, pair<int,int> > edges[MN];
int cx[MN], cy[MN], sx, sy;

void get(Writing &cur) {
    cin >> cur.nStroke;
    id.clear();
    FOR(i,1,cur.nStroke) {
        cin >> edges[i].first.first >> edges[i].first.second;
        cin >> edges[i].second.first >> edges[i].second.second;

        id[edges[i].first] = 1;
        id[edges[i].second] = 1;
    }

    cur.nPoint = id.size();

    int now = 0;
    for(__typeof(id.begin()) it = id.begin(); it != id.end(); ++it)
        id[it->first] = ++now;

    // Calculate directions
    memset(cur.c, 0, sizeof cur.c);
    FOR(i,1,cur.nStroke) {
        cur.c[id[edges[i].first]][id[edges[i].second]] = 1;
    }

    // Calculate positions
    sx = sy = 0;
    for(__typeof(id.begin()) it = id.begin(); it != id.end(); ++it) {
        cx[++sx] = it->first.first;
        cy[++sy] = it->first.second;
    }
    sort(cx+1, cx+sx+1); sx = unique(cx+1, cx+sx+1) - cx - 1;
    sort(cy+1, cy+sy+1); sy = unique(cy+1, cy+sy+1) - cy - 1;

    int i = 0;
    for(__typeof(id.begin()) it = id.begin(); it != id.end(); ++it) {
        cur.pos[++i] = make_pair(
            lower_bound(cx+1, cx+sx+1, it->first.first) - cx,
            lower_bound(cy+1, cy+sy+1, it->first.second) - cy
        );
    }
}

bool equals(const Writing &a, const Writing &b) {
    if (a.nPoint != b.nPoint) return false;
    if (a.nStroke != b.nStroke) return false;

    FOR(i,1,a.nPoint) FOR(j,1,a.nPoint)
        if (a.c[i][j] != b.c[i][j]) return false;

    FOR(i,1,a.nPoint)
        if (a.pos[i] != b.pos[i]) return false;
    return true;
}

int main() {
    freopen("japanese.in", "r", stdin);
    freopen("japanese.out", "w", stdout);
    ios :: sync_with_stdio(false);
    int n; cin >> n;
    get(first);
    FOR(i,2,n) {
        get(cur);
        if (equals(cur, first)) puts("CORRECT");
        else puts("INCORRECT");
    }
    return 0;
}
