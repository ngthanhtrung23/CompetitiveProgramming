#include <iomanip>
#include <sstream>
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
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

const double PI = acos(-1.0);

int f[5000111], n, a[1000111];

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//    scanf("%d", &n); FOR(i,1,n) scanf("%d", &a[i]);
    GN(n); FOR(i,1,n) GN(a[i]);
    memset(f, -1, sizeof f);
    FOR(i,1,n) f[a[i]] = a[i];
    REP(mask,TWO(22)) if (f[mask] < 0) {
        REP(bit,22) if (CONTAIN(mask,bit)) {
            if (f[mask - TWO(bit)] >= 0) {
                f[mask] = f[mask - TWO(bit)];
                break;
            }
        }
    }
    FOR(i,1,n) {
        printf("%d ", f[TWO(22) - 1 - a[i]]);
    }
    puts("");
    return 0;
}
