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
const int MN = 100111;

long long ip[MN];
char s[1011];
int n, k;

int main() {
    while (scanf("%d%d\n", &n, &k) == 2) {
        FOR(i,1,n) {
            gets(s);
            REP(x,strlen(s)) if (s[x] == '.') s[x] = ' ';
            long long cur = 0, u;
            istringstream sin(s);
            while (sin >> u) {
                cur = cur * 256LL + u;
            }
            ip[i] = cur;
        }

        long long full = (1LL << 32) - 1;
        set<long long> s;
        bool ok = false;
        long long save = -1;
        REP(bit,32) {
            s.clear();
            FOR(i,1,n)
                s.insert(ip[i] & full);

            if (s.size() == k) {
                ok = true;
                save = full;
            }
            full -= 1LL << bit;
        }
        if (!ok) {
            puts("-1");
            continue;
        }
        vector<int> res;
        res.clear();
        full = save;
        REP(i,4) {
            res.push_back(full % 256);
            full /= 256;
        }
        FORD(i,3,0) {
            cout << res[i];
            if (i) putchar('.');
        }
        puts("");
    }
    return 0;
}
