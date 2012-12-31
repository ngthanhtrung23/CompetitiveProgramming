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

char s[100111], t[100111];
int cs[300], ct[300], l;

int get() {
    int res = 0;
    FOR(c,'A','Z') {
        if (ct[c] > cs[c])
            res += ct[c] - cs[c];
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (gets(s)) {
        gets(t);
        memset(cs, 0, sizeof cs);
        memset(ct, 0, sizeof ct);
        l = strlen(s);
        REP(i,l) {
            cs[s[i]]++;
            ct[t[i]]++;
        }

        int optimal = get(), changed = 0;

        REP(i,l) {
            FOR(cur,'A','Z') if (ct[cur]) {
                cs[s[i]]--; cs[cur]++;

                ct[cur]--; cs[cur]--;
                int now = changed + get();
                ct[cur]++; cs[cur]++;

                if (cur != s[i]) ++now;

                if (now == optimal) {
                    if (cur != s[i]) ++changed;
                    s[i] = cur;
                    ct[cur]--; cs[cur]--;
                    break;
                }

                cs[s[i]]++; cs[cur]--;
            }
        }
        printf("%d\n", optimal);
        puts(s);
    }
    return 0;
}
