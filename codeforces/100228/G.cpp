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

char a[155][155];
set<string> has;
int m, n;

struct Node {
    string rep;
    bool black, white;
} tree[200111];

void buildTree(int i, int r1, int r2, int c1, int c2) {
    if (r1 == r2) {
        tree[i].rep = "";
        tree[i].rep += a[r1][c1];
        if (a[r1][c1] == '0') tree[i].white = true, tree[i].black = false;
        else tree[i].black = true, tree[i].white = false;
        return ;
    }

    int rmid = (r1 + r2) >> 1;
    int cmid = (c1 + c2) >> 1;

    buildTree((i<<2)-2, r1, rmid, c1, cmid);
    buildTree((i<<2)-1, r1, rmid, cmid+1, c2);
    buildTree((i<<2)-0, rmid+1, r2, c1, cmid);
    buildTree((i<<2)+1, rmid+1, r2, cmid+1, c2);

    string a = tree[(i<<2)-2].rep;
    string b = tree[(i<<2)-1].rep;
    string c = tree[(i<<2)-0].rep;
    string d = tree[(i<<2)+1].rep;

    char bound = 'A';
    REP(t,a.length()) if (a[t] >= 'A' && a[t] <= 'Z') bound = a[t] + 1;
    REP(t,b.length()) if (b[t] >= 'A' && b[t] <= 'Z') bound = b[t] + 1;
    REP(t,c.length()) if (c[t] >= 'A' && c[t] <= 'Z') bound = c[t] + 1;
    REP(t,d.length()) if (d[t] >= 'A' && d[t] <= 'Z') bound = d[t] + 1;

    tree[i].rep = "";
    tree[i].rep += tree[(i<<2)-2].rep; tree[i].rep += bound;
    tree[i].rep += tree[(i<<2)-1].rep; tree[i].rep += bound;
    tree[i].rep += tree[(i<<2)-0].rep; tree[i].rep += bound;
    tree[i].rep += tree[(i<<2)+1].rep;

    tree[i].white = tree[(i<<2)-2].white && tree[(i<<2)-1].white && tree[(i<<2)-0].white && tree[(i<<2)+1].white;
    tree[i].black = tree[(i<<2)-2].black && tree[(i<<2)-1].black && tree[(i<<2)-0].black && tree[(i<<2)+1].black;

    if (tree[i].white) tree[i].rep = "0";
    if (tree[i].black) tree[i].rep = "1";
}

int get1(int i, int r1, int r2, int c1, int c2) {
    int res;
    if (tree[i].black || tree[i].white) {
        res = 1;
    }
    else {
        int rmid = (r1 + r2) >> 1;
        int cmid = (c1 + c2) >> 1;

        res = get1((i<<2)-2, r1, rmid, c1, cmid)
            + get1((i<<2)-1, r1, rmid, cmid+1, c2)
            + get1((i<<2)-0, rmid+1, r2, c1, cmid)
            + get1((i<<2)+1, rmid+1, r2, cmid+1, c2)
            + 1;
    }
    return res;
}

int get2(int i, int r1, int r2, int c1, int c2) {
    int res;

    if (tree[i].black || tree[i].white) res = 1;
    else if (has.find(tree[i].rep) != has.end()) res = 0;
    else {
        int rmid = (r1 + r2) >> 1;
        int cmid = (c1 + c2) >> 1;

        res = get2((i<<2)-2, r1, rmid, c1, cmid)
            + get2((i<<2)-1, r1, rmid, cmid+1, c2)
            + get2((i<<2)-0, rmid+1, r2, c1, cmid)
            + get2((i<<2)+1, rmid+1, r2, cmid+1, c2)
            + 1;
        has.insert(tree[i].rep);
    }
    return res;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2 && (m || n)) {
        memset(a, '0', sizeof a);
        FOR(i,1,m) {
            scanf("%s\n", &a[i][1]);
            a[i][n+1] = '0';
        }
        has.clear();

        while (__builtin_popcount(m) != 1) ++m;
        while (__builtin_popcount(n) != 1) ++n;

        m = n = max(m, n);

        buildTree(1, 1, m, 1, n);
        int ans1 = get1(1, 1, m, 1, n);
        int ans2 = get2(1, 1, m, 1, n);

        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
