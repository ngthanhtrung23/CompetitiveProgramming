#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
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

const long double PI = acos((long double) -1.0);
const int MN = 200111;

vector< vector< string > > images;
int nImage, m, n;
char tmp[MN];
int t[MN];

vector<int> ke[MN*3];
int vao[MN*3];

void addEdge(int a, int b) {
    ke[a].push_back(b);
    vao[b]++;
}

void initGraph() {
    int id = nImage;
    FOR(i,1,m) FOR(j,1,n) {
        ++id;
        FOR(img,1,nImage)
            if (images[img][i][j] == '1') {
                addEdge(img, id);
            }
            else addEdge(id, img);
    }
}

int st[MN*3], top, x[MN*3];

void solve() {
    top = 0;
    FOR(i,1,m*n+nImage) if (vao[i] == 0) {
        st[++top] = i;
    }

    int now = 0;

    while (top) {
        int u = st[top--];
        if (u <= nImage) x[++now] = u;

        REP(i,ke[u].size()) {
            int v = ke[u][i];
            vao[v]--;
            if (vao[v] == 0) {
                st[++top] = v;
            }
        }
    }

    if (now < nImage) {
        puts("IMPOSSIBLE");
        return ;
    }

    FOR(i,1,nImage) {
        t[x[i]] = t[x[i-1]] + 1;
    }
    FOR(i,1,m) FOR(j,1,n) {
        int val = 0;
        FOR(img,1,nImage)
            if (images[img][i][j] == '1')
                val = max(val, t[img]);
        printf("%d ", val);
        if (j == n) puts("");
    }
    FOR(i,1,nImage) printf("%d ", t[i]);
    puts("");
}

int main() {
    while (scanf("%d%d%d\n", &nImage, &m, &n) == 3) {
        images.clear();
        images.resize(nImage+1);

        memset(vao, 0, sizeof vao);
        FOR(i,1,nImage+m*n) ke[i].clear();

        FOR(img,1,nImage) {
            images[img].resize(m+1);
            FOR(i,1,m) {
                scanf("%s\n", &tmp);
                images[img][i] = " " + string(tmp);
            }
        }

        initGraph();
        solve();
    }
    return 0;
}
