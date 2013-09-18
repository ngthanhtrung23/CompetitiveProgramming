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

int to[611][33];
int n, l, m;
string a[611];
map<string,int> id;
long long f[111][611];

int main() {
    // freopen("input.txt", "r", stdin);
    ios :: sync_with_stdio(false);
    while (cin >> n >> l >> m && (n || l || m)) {
        id.clear();
        int cur = 0;
        FOR(i,1,m) {
            cin >> a[++cur];
            if (id.find(a[cur]) != id.end()) --cur;
            else id[a[i]] = i;
        }
        m = cur;

        if (l < a[1].size()) {
            long long res = 0;
            FOR(i,1,l) res = res * n;
            cout << res << endl;
            continue;
        }

        memset(to, -1, sizeof to);
        memset(f, 0, sizeof f);

        FOR(i,1,m) {
            FOR(c,'A','A'+n-1) {
                string next = a[i].substr(1, a[i].length()-1);
                next += c;

                if (id.find(next) != id.end()) {
                    to[i][c-'A'] = id[next];
                }
                else to[i][c-'A'] = -1;
            }
            f[a[1].size()][i] = 1;
        }

        FOR(i,a[1].size(),l-1) FOR(last,1,m) if (f[i][last]) {
            REP(add,n) {
                int next = to[last][add];
                if (next < 0) continue;

                f[i+1][next] += f[i][last];
            }
        }

        long long res = 0;
        FOR(i,1,m)
            res += f[l][i];
        cout << res << endl;
    }
    return 0;
}
