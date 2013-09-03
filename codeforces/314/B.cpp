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

int b, d;
string a, c;
pair<int,int> f[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> b >> d) {
        cin >> a >> c;
        int la = a.length(), lc = c.length();
        a = " " + a; c = " " + c;

        FOR(start,0,lc-1) {
            f[start] = make_pair(0, start);

            int j = start + 1;
            FOR(i,1,la) {
                if (a[i] == c[j]) {
                    ++j;
                    if (j > lc) {
                        j = 1;
                        ++f[start].first;
                    }
                }
            }
            f[start].second = j - 1;

            // cout << f[start].first << ' ' << f[start].second << endl;
        }

        int cnt = 0, start = 0;
        FOR(i,1,b) {
            cnt += f[start].first;
            start = f[start].second;
        }
        cout << cnt / d << endl;
    }
    return 0;
}
