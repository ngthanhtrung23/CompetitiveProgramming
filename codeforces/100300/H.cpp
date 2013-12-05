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

const string rep[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
const int val[] =    {1,   4,    5,   9,    10,  40,   50,  90,   100, 400,  500, 900,  1000};

string roman(int n) {
    string res = "";
    while (n > 0) {
        FORD(x,12,0) {
            if (n >= val[x]) {
                n -= val[x];
                res += rep[x];
                break;
            }
        }
    }
    return res;
}

int m, n;
char a[111][111];
bool visited[111][111];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool check(int i, int j, int pos, const string &need) {
    if (pos == need.length()-1) {
        return j == n;
    }
    REP(dir,4) {
        int ii = i + di[dir], jj = j + dj[dir];
        if (ii < 1 || ii > m || jj < 1 || jj > n) continue;
        if (visited[ii][jj] || a[ii][jj] != need[pos+1]) continue;

        visited[ii][jj] = true;
        if (check(ii, jj, pos+1, need)) return true;
        visited[ii][jj] = false;
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        bool has_solution = false;

        FOR(t,1,3999) {
            string need = roman(t);
            bool good = false;
            FOR(i,1,m) if (a[i][1] == need[0]) {
                memset(visited, false, sizeof visited);
                if (check(i, 1, 0, need)) {
                    good = true;
                    break;
                }
            }
            if (good) {
                puts(need.c_str());
                has_solution = true;
                break;
            }
        }
        if (!has_solution) puts("NO");
    }
    return 0;
}
