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

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

char s[MN], tmp[111];
int next[MN][30], nId;
map<int,int> id;
int query[10111], q, n, res[10111];

void init() {
    n = strlen(s);
    REP(i,n) {
        if (i == 0) {
            FOR(c,0,'z'-'a') next[i][c] = -1;
            next[i][s[0]-'a'] = 0;
        }
        else {
            FOR(c,0,'z'-'a') next[i][c] = next[i-1][c];
            next[i][s[i]-'a'] = i;
        }

        // PR0(next[i], 'z'-'a');
    }
}

pair<int,char> cur[33];
int nCur;

void solve() {
    // puts("----");
    REP(i,n) { // consider strings ending at i
        // DEBUG(i);
        int bound = (i == n-1) ? -1 : (next[i][s[i+1] - 'a']);

        nCur = 0;
        FOR(c,0,'z'-'a')
        if (next[i][c] >= 0 && next[i][c] > bound) {
            ++nCur;
            cur[nCur] = make_pair(next[i][c], c);
        }

        sort(cur+1, cur+nCur+1);

        // FOR(i,1,nCur) cout << (char) ('a' + cur[i].second) << ' ' << cur[i].first << "   ";
        // cout << endl;

        int mask = 0;
        FORD(i,nCur,1) {
            mask |= TWO(cur[i].second);
            if (id.find(mask) != id.end()) {
                ++res[id[mask]];
            }
        }
    }
    FOR(i,1,q) printf("%d\n", res[id[query[i]]]);
}

int main() {
    while (gets(s)) {
        nId = 0;
        memset(res, 0, sizeof res);
        id.clear();

        scanf("%d\n", &q);
        FOR(i,1,q) {
            gets(tmp);
            int l = strlen(tmp);
            int mask = 0;
            REP(x,l) {
                mask |= TWO(tmp[x] - 'a');
            }
            // cout << mask << endl;
            query[i] = mask;
            if (id.find(mask) == id.end()) id[mask] = ++nId;
        }

        init();
        solve();
    }
    return 0;
}
