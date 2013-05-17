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
const int MN = 2000111;

int a[MN];
long long n, l, t;

int main() {
    while (cin >> n >> l >> t) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,n+1,n+n) a[i] = a[i-n] + l;

        long long cnt = 0;

        long long turn = t / l; t %= l;

        // Xuoi
        int j1 = 1, j2 = 1;
        FOR(i,1,n) {
            if (j1 < i) j1 = i;
            if (j2 < i) j2 = i;

            while (j1 < i+n-1 && a[j1+1] - a[i] <= t+t) ++j1;
            while (j2 < i+n-1 && a[j2+1] - a[i] <= -l + t + t) ++j2;

            cnt += (j2-i) + (j1-i) * (2 * turn + 1) + (n - (j1-i) - 1) * (2 * turn);
        }

        cout << (fixed) << setprecision(6) << (cnt * (long double) 0.25) << endl;
    }
    return 0;
}
