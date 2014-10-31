#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

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
const int MN = 3000111;

int n, a[MN], current;
#define next next_
int eu[MN], head[MN], next[MN];

void dfs1(int u) {
    a[u] = 1;
    for(int p = head[u]; p > 0; p = next[p]) {
        int v = eu[p];
        dfs1(v);

        a[u] += a[v];
    }
}

int cnt[MN];

bool check() {
    int total = 0;
    for(int i = current; i <= n; i += current) {
        total += cnt[i];
    }
    return total == n / current;
}

int main() {
    GN(n);
    FOR(v,2,n) {
        int u; GN(u);
        eu[v] = v;
        next[v] = head[u];
        head[u] = v;
    }
    vector<int> res;
    dfs1(1);
    FOR(i,1,n) cnt[a[i]]++;
    for(int i = 1; i*i <= n; ++i)
        if (n % i == 0) {
            current = i;
            if (check()) res.push_back(n/i);

            if (i*i != n) {
                current = n / i;
                if (check()) res.push_back(i);
            }
        }
    sort(res.begin(), res.end());
    REP(i,res.size()) printf("%d ", res[i]); printf("\n");
    return 0;
}

