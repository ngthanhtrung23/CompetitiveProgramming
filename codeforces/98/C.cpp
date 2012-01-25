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

long long a, b, l;

long double f(long double x0) {
    long double y0 = sqrt(l*(long double)l - x0*x0);
    return (b *y0 + a *x0 - x0*y0) / l;
}

long double get(long double left, long double right) {
    if (right - left <= 1e-10) return f(left);
    long double x1 = (left * 2 + right) / 3;
    long double x2 = (left + right * 2) / 3;
    long double y1 = f(x1), y2 = f(x2);
    
    if (y1 <= y2) return get(left, x2);
    else return get(x1, right);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (cin >> a >> b >> l) {
        if (a > b) swap(a, b);
        if (l <= a) {
            cout << l << endl;
            continue;
        }
        if (l <= b) {
            cout << a << endl;
            continue;
        }
        long double res = min(min(f(0), f(l)), get(0, l));
        if (res < 0) puts("My poor head =(");
        else cout << (fixed) << setprecision(8) << res << endl;
    }
    return 0;
}
