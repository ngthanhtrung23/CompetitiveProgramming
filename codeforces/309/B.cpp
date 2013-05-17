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
const int MN = 1000111;

int f[22][MN], g[22][MN], a[MN], sum[MN];
char tmp[MN * 10];
string s[MN];
int n, r, c;

int main() {
    while (scanf("%d%d%d", &n, &r, &c) == 3) {
        FOR(i,1,n) {
            scanf("%s", &tmp[0]);
            a[i] = strlen(tmp);
            s[i] = string(tmp);
            sum[i] = sum[i-1] + a[i];
        }
        int res = 0, savej = -1, savei = -1;
        REP(t,20) {
            FOR(j,1,n) {
                f[t][j] = j-1;
                if (a[j] > c) continue;

                if (t == 0) {
                    int l = j, r = n, res = j;
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (sum[mid] - sum[j-1] + mid - j <= c) {
                            res = mid;
                            l = mid + 1;
                        }
                        else r = mid - 1;
                    }
                    f[t][j] = res;
                }
                else {
                    int i = f[t-1][j];
                    if (i < n) f[t][j] = f[t-1][i+1];
                    else f[t][j] = i;
                }
            }

            FOR(j,1,n) {
                if (r & (1<<t)) {
                    if (t == 0) {
                        g[t][j] = f[t][j];
                    }
                    else {
                        int i = g[t-1][j];
                        if (i < n) g[t][j] = f[t][i+1];
                        else g[t][j] = i;
                    }
                }
                else {
                    if (t == 0) {
                        g[t][j] = j-1;
                    }
                    else {
                        g[t][j] = g[t-1][j];
                    }
                }
                if (t == 19 && g[t][j] - j + 1 > res) {
                    res = g[t][j] - j + 1;
                    savej = j;
                    savei = g[t][j];
                }
            }
        }
        if (res == 0) {
            puts("");
        }
        else {
            int j = savej;
            FOR(rr,1,r) {
                bool first = true;
                int cur = 0;
                if (j > n) break;

                while (true) {
                    // Add jth word to current line
                    if (!first) ++cur;
                    cur += a[j];
                    if (cur > c) break;
                    if (first) first = false; else putchar(' ');
                    printf("%s", s[j].c_str());
                    ++j;
                    if (j > n) break;
                }
                puts("");
            }
        }
    }
    return 0;
}
