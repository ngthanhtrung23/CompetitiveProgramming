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

char a[11][11];
char s[100111];
bool mark[11][11];

void king(int i, int j) {
    FOR(ii,i-1,i+1) FOR(jj,j-1,j+1) mark[ii][jj] = true;
}

void knight(int i, int j) {
    FOR(di,-2,2) FOR(dj,-2,2) if (di*di + dj*dj == 5) {
        int ii = i + di, jj = j + dj;
        if (ii > 0 && ii < 9 && jj > 0 && jj < 9) mark[ii][jj] = true;
    }
}

void bishop(int i, int j) {
    const int di[] = {-1,1,-1,1};
    const int dj[] = {-1,-1,1,1};

    REP(dir,4) {
        int ii = i + di[dir], jj = j + dj[dir];
        while (a[ii][jj] == ' ') {
            mark[ii][jj] = true;
            ii += di[dir]; jj += dj[dir];
        }
    }
}

void rook(int i, int j) {
    const int di[] = {-1,1,0,0};
    const int dj[] = {0,0,-1,1};

    REP(dir,4) {
        int ii = i + di[dir], jj = j + dj[dir];
        while (a[ii][jj] == ' ') {
            mark[ii][jj] = true;
            ii += di[dir]; jj += dj[dir];
        }
    }
}

void queen(int i, int j) {
    bishop(i, j);
    rook(i, j);
}

void pawn(int i, int j) {
    if (a[i][j] == 'p') {
        mark[i+1][j-1] = mark[i+1][j+1] = true;
    }
    else {
        mark[i-1][j-1] = mark[i-1][j+1] = true;
    }
}

int main() {
    while (gets(s)) {
        REP(i,strlen(s)) if (s[i] == '/') s[i] = ' ';
        istringstream ss(s);
        memset(a, 'X', sizeof a);
        FOR(i,1,8) {
            string cur; ss >> cur;

            int j = 0;
            REP(t,cur.length()) {
                char c = cur[t];
                if (c >= '0' && c <= '9') {
                    int x = c - '0';
                    while (x--) {
                        a[i][++j] = ' ';
                    }
                }
                else a[i][++j] = cur[t];
            }
        }

        memset(mark, false, sizeof mark);

        FOR(i,1,8) FOR(j,1,8) if (a[i][j] != ' ') {
            mark[i][j] = true;
            if (a[i][j] == 'k' || a[i][j] == 'K') king(i, j);
            if (a[i][j] == 'r' || a[i][j] == 'R') rook(i, j);
            if (a[i][j] == 'n' || a[i][j] == 'N') knight(i, j);
            if (a[i][j] == 'b' || a[i][j] == 'B') bishop(i, j);
            if (a[i][j] == 'q' || a[i][j] == 'Q') queen(i, j);
            if (a[i][j] == 'p' || a[i][j] == 'P') pawn(i, j);
        }

        int res = 0;
        FOR(i,1,8) FOR(j,1,8) if (!mark[i][j]) ++res;
        cout << res << endl;
    }
    return 0;
}