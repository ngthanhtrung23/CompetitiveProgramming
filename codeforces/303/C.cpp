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

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

int n, a[5011], k;
vector< int > bad[1000111];
bool mark[1000111], allocated[1000111];
vector<int> affected;

void init() {
    memset(mark, false, sizeof mark);
    FOR(i,0,1000011) bad[i].clear();
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        init();

        FOR(i,1,n) scanf("%d", &a[i]);
        sort(a+1, a+n+1);

        FOR(i,1,n) FOR(j,i+1,n) {
            int diff = a[j] - a[i];
            if (bad[diff].size() <= 2*(k+1)) {
                bad[diff].push_back(a[i]);
                bad[diff].push_back(a[j]);
            }
        }

        FOR(mod,1,1000001) {
            affected.clear();
            int need = 0;

            for(int i = mod; i <= 1000001; i += mod) {
                if (bad[i].size() > k * 2) {
                    need = 1000;
                    break;
                }

                REP(t,bad[i].size()) {
                    if (!allocated[bad[i][t]]) {
                        if (!mark[bad[i][t] % mod]) mark[bad[i][t] % mod] = true;
                        else ++need;
                        allocated[bad[i][t]] = true;
                        affected.push_back(bad[i][t]);
                    }
                }
                if (need > k) break;
            }

            if (need <= k) {
                printf("%d\n", mod);
                break;
            }

            REP(i,affected.size()) {
                mark[affected[i] % mod] = false;
                allocated[affected[i]] = false;
            }
        } // for mod

    } // test
}
