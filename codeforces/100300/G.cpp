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

int m, n;
char c[111][111];

pair<char, pair<int,int> > get() {
    FOR(i,1,m) FOR(j,1,n)
    if (c[i][j] != '.') return make_pair(c[i][j], make_pair(i,j));
    return make_pair('X', make_pair(0, 0));
}

bool check() {
    pair<char, pair<int,int> > res = get();
    char good = res.first;
    if (good == 'X') return false;

    FOR(i,1,m) FOR(j,1,n)
        if (c[i][j] != '.' && c[i][j] != good) return false;

    int i = res.second.first, j = res.second.second;
    if (good == '-') {
        while (j <= n && c[i][j] == '-') {
            c[i][j] = '.';
            ++j;
        }
    }
    if (good == '|') {
        while (i <= m && c[i][j] == '|') {
            c[i][j] = '.';
            ++i;
        }
    }
    if (good == '/') {
        while (i <= m && j >= 1 && c[i][j] == '/') {
            c[i][j] = '.';
            ++i;
            --j;
        }
    }
    if (good == '\\') {
        while (i <= m && j <= n && c[i][j] == '\\') {
            c[i][j] = '.';
            ++i;
            ++j;
        }
    }

    res = get();
    return res.first == 'X';
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> m >> n;
        FOR(i,1,m) FOR(j,1,n) cin >> c[i][j];

        if (check()) puts("CORRECT");
        else puts("INCORRECT");
    }
    return 0;
}
