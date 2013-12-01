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

int ntest;
int n, a[10111];
vector< pair<int,int> > res;

int indexOf(int k) {
    FOR(i,k,n) if (a[i] == k) return i;
    return -1;
}

void move(int i, int start) {
    while (start < i) {
        // DEBUG(i);
        int l = start, r = i;
        if ((r - l + 1) & 1) ++r;
        if (r > n) {
            --r;
            ++l;
        }
        int len = (r - l + 1) >> 1;

        res.push_back(make_pair(l, r));

        for(int turn = 0, x = l; turn < len; ++turn, ++x)
            swap(a[x], a[x+len]);

        // PR(a, n);
        i = indexOf(start);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n; FOR(i,1,n) cin >> a[i];
        res.clear();
        FOR(start,1,n) {
            int i = indexOf(start);
            // DEBUG(i);
            move(i, start);
        }
        FOR(i,1,n) if (a[i] != i) puts(":@)");
        printf("%d\n", res.size());
        REP(i,res.size()) printf("%d %d\n", res[i].first, res[i].second);
    }
    return 0;
}
