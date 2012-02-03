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

long double savef[1011][1011], saveg[1011][1011];

long double g(int w, int b);

long double f(int w, int b) { // Princess win
    if (savef[w][b] >= 0) return savef[w][b];
    if (w <= 0) return 0.0;
    if (b < 0) return 0.0;
    if (b == 0) return 1.0;
    return savef[w][b] = w / (long double) (w + b) + b / (long double) (w + b) * (1 - g(w, b-1));
}

long double g(int w, int b) { // Princess not win, Dragon move first
    if (saveg[w][b] >= 0) return saveg[w][b];
    long double res = 0.0;
    // Dragon win 1st round
//    cout << w << ' ' << b << ' ';
    res += w / (long double) (w + b);
//    cout << res << ' ';
    // Dragon not win 1st round --> b / (w + b); state = (w, b-1)
    // White mouse move out: b/(w+b) * w/(w+b-1); state = (w-1, b-1)
    if (b > 0 && w > 0) {
        res += b / (long double) (w + b) * w / (w + b - 1) * (1 - f(w-1, b-1));
    }
//    cout << res << ' ';
    // Black mouse move out: b/(w+b) * (b-1)/(w+b-1); state = (w, b-2)
    if (b > 2) {
        res += b / (long double) (w + b) * (b-1) / (w + b - 1) * (1 - f(w, b-2));
    }
//    cout << res << endl;
    return saveg[w][b] = res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int w, b;
    cin >> w >> b;
    FOR(i,0,w) FOR(j,0,b) savef[i][j] = saveg[i][j] = -1;
    cout << (fixed) << setprecision(10) << f(w, b);
    return 0;
}
