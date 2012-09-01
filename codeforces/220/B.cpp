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
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

int n, m, a[MN];
vector<int> x[MN];
map<int,int> cnt, ind;
vector<int> need;

int main() {
    GN(n); GN(m);
    cnt.clear();
    FOR(i,1,n) {
        GN(a[i]);
        ++cnt[a[i]];
    }
    need.clear(); ind.clear();
    for(map<int,int> :: iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->S >= it->F) {
            ind[it->F] = need.size();
            need.PB(it->F);
        }
    }

    FOR(i,1,n) if (ind.find(a[i]) != ind.end()) {
        int u = ind[a[i]];
        x[u].PB(i);
    }

    // REP(t,need.size()) {
    //     cout << need[t] << ": ";
    //     PR0(x[t], x[t].size());
    // }

    while (m--) {
        int l, r; GN(l); GN(r);
        int savel = l, saver = r;
        int res = 0;
        REP(t,need.size()) {
            l = savel, r = saver;
            int sz = x[t].size();
            if (l > x[t][sz-1] || r < x[t][0]) continue;

            if (l < x[t][0]) l = x[t][0];
            if (r > x[t][sz-1]) r = x[t][sz-1];
            int u = lower_bound(x[t].begin(), x[t].end(), l) - x[t].begin();
            int v = lower_bound(x[t].begin(), x[t].end(), r) - x[t].begin();

            if (x[t][v] > r) --v;
            if (v - u + 1 == need[t]) ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}
