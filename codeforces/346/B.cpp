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

int nextVirus[111][333], next1[111][333], next2[111][333];
int f[111][111][111], res, tr1[111][111][111], tr2[111][111][111], tr3[111][111][111];
string s1, s2, virus;

void trace(int l, int i1, int i2, int i3) {
    if (l == 0) return ;
    trace(l-1, tr1[i1][i2][i3], tr2[i1][i2][i3], tr3[i1][i2][i3]);
    putchar(s1[i1-1]);
}

int main() {
    while (cin >> s1 >> s2 >> virus) {
        memset(f, -1, sizeof f);

        FOR(i,0,virus.length()-1) {
            FOR(c,'A','Z') {
                string cur = virus.substr(0, i);
                cur += c;
                FORD(j,i+1,0) {
                    string need = virus.substr(0, j);
                    if (cur.substr(cur.length()-need.length(), need.length()) == need) {
                        nextVirus[i][c] = j;
                        break;
                    }
                }
            }
            // FOR(c,'A','Z') cout << nextVirus[i][c] << ' '; cout << endl;
        }
        FOR(i,0,s1.length()) FOR(c,'A','Z') {
            int j = i;
            while (j < s1.length() && s1[j] != c) ++j;
            next1[i][c] = j;
        }
        FOR(i,0,s2.length()) FOR(c,'A','Z') {
            int j = i;
            while (j < s2.length() && s2[j] != c) ++j;
            next2[i][c] = j;
        }

        f[0][0][0] = 0;
        res = 0;
        int save1, save2, save3;
        FOR(i1,0,s1.length()-1) FOR(i2,0,s2.length()-1) FOR(iv,0,virus.length()-1) {
            FOR(c,'A','Z') {
                int j1 = next1[i1][c], j2 = next2[i2][c], jv = nextVirus[iv][c];
                if (j1 >= s1.length() || j2 >= s2.length() || jv >= virus.length())
                    continue;

                if (f[i1][i2][iv] + 1 > f[j1+1][j2+1][jv]) {
                    f[j1+1][j2+1][jv] = f[i1][i2][iv] + 1;
                    tr1[j1+1][j2+1][jv] = i1;
                    tr2[j1+1][j2+1][jv] = i2;
                    tr3[j1+1][j2+1][jv] = iv;
                    if (f[j1+1][j2+1][jv] > res) {
                        res = f[j1+1][j2+1][jv];
                        save1 = j1+1;
                        save2 = j2+1;
                        save3 = jv;
                    }
                }
            }
        }
        if (res == 0) puts("0");
        else {
            trace(res, save1, save2, save3);
            puts("");
        }
    }
    return 0;
}
