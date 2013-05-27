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
const int MN = 100111;

long long h;
int n, m, k;
long long a[MN];
int c[MN];
bool good[MN];

long long go[22];
int nGo;
long long f[MN];

set< pair<long long,int> > s;

set< pair<int, int> > all;

void dijkstra() {
    f[0] = 0;
    FOR(i,1,k-1) f[i] = 1000111000111000111LL;

    s.clear();
    s.insert(make_pair(0, 0));

    while (!s.empty()) {
        int u = s.begin()->second;
        long long l = s.begin()->first;
        s.erase(s.begin());

        if (f[u] != l) continue;
        FOR(i,1,nGo) {
            int v = (u + go[i]) % k;
            if (f[v] > f[u] + go[i]) {
                f[v] = f[u] + go[i];
                s.insert(make_pair(f[v], v));
            }
        }
    }

    FOR(i,1,n) if (!good[i] && f[a[i]%k] <= a[i]) {
        good[i] = true;
        all.insert(make_pair(-c[i], i));
    }
}

int main() {
    GN(h); GN(n); GN(m); GN(k);
    FOR(i,1,n) {
        GN(a[i]); --a[i];
        GN(c[i]);
    }
    dijkstra();
    while (m--) {
        int t; GN(t);
        if (t == 1) {
            long long x; GN(x);
            go[++nGo] = x;
            dijkstra();
        }
        else if (t == 2) {
            int x, y; GN(x); GN(y);
            if (good[x] && all.find(make_pair(-c[x], x)) != all.end()) {
                all.erase(all.find(make_pair(-c[x], x)));
                c[x] -= y;
                all.insert(make_pair(-c[x], x));
            }
            else {
                c[x] -= y;
            }
        }
        else {
            if (all.size() == 0) puts("0");
            else {
                printf("%d\n", -all.begin()->first);
                all.erase(all.begin());
            }
        }
        // cout << "Reachable: ";
        // for(set< pair<int,int> > :: iterator it = all.begin(); it != all.end(); ++it)
        //     cout << -it->first << ' ' << it->second << "   ";
        // cout << endl;
    }
    return 0;
}
