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
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

int INP,AM;
#define BUFSIZE (1<<10)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF,0,sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

const double PI = acos(-1.0);

bool good(char c) {
    if (c == 'a' || c == 'A') return true;
    if (c == 'e' || c == 'E') return true;
    if (c == 'i' || c == 'I') return true;
    if (c == 'o' || c == 'O') return true;
    if (c == 'u' || c == 'U') return true;
    return false;
}

char s[200111];
int bit[600111], c[200111], v[200111];

#define _(u) (u&(-u))

int get(int u) {
    int res = 1000111;
    while (u > 0) {
        res = min(res, bit[u]);
        u -= _(u);
    }
    return res;
}

void update(int u, int k) {
    while (u <= 600011) {
        bit[u] = min(bit[u], k);
        u += _(u);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(s);
    int n = strlen(s);
    int res = 0, cnt = 0;
    REP(i,n) {
        if (i) {
            c[i] = c[i-1];
            v[i] = v[i-1];
        }
        if (good(s[i])) v[i]++;
        else c[i]++;
    }
    REP(i,n) {
        v[i] = 2*c[i] - v[i] + 200001;
    }
    FOR(i,0,600110) bit[i] = 1000111;
    update(200001, -1);
    REP(j,n) {
        int i = get(v[j]);
        //cout << j << ' ' << (v[j]) << ' ' << i << endl;
        if (i <= j) {
            int l = j - i;
            if (l > res) {
                res = l;
                cnt = 1;
            }
            else if (res == l) {
                cnt++;
            }
        }
        update(v[j], j);
    }
    if (res == 0) puts("No solution");
    else cout << res << ' ' << cnt << endl;
    return 0;
}
