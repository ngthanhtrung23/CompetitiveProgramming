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
const int oo = 1000111000;
const int MN = 100111;

int n, m;
vector< pair<int,int> > ke[MN];
set<int> arrive[MN];

set< pair<int,int> > s;
int f[MN];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) {
            ke[i].clear();
            arrive[i].clear();
            f[i] = oo;
        }

        while (m--) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }

        FOR(i,1,n) {
            int k; scanf("%d", &k);
            while (k--) {
                int t; scanf("%d", &t);
                arrive[i].insert(t);
            }
        }

        f[1] = 0; s.insert(make_pair(0, 1));
        bool ok = false;
        while (!s.empty()) {
            int l = s.begin()->first, u = s.begin()->second;
            s.erase(s.begin());
            if (l != f[u]) continue;

            if (u == n) {
                printf("%d\n", f[u]);
                ok = true;
                break;
            }

            while (arrive[u].find(l) != arrive[u].end()) ++l;

            REP(i,ke[u].size()) {
                int v = ke[u][i].first, c = ke[u][i].second;
                if (f[v] > l + c) {
                    f[v] = l + c;
                    s.insert(make_pair(f[v], v));
                }
            }
        }
        // PR(f, n);
        if (!ok) puts("-1");
    }
    return 0;
}
