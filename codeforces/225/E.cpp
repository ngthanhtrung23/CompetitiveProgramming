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

const int p[] = {1, 2, 4, 6, 12, 16, 18, 30, 60, 88, 106, 126, 520, 606, 1278, 2202, 2280, 
    3216, 4252, 4422, 9688, 9940, 11212, 19936, 21700, 23208, 44496, 86242, 110502, 132048, 
    216090, 756838, 859432, 1257786, 1398268, 2976220, 3021376, 6972592, 13466916, 20996010};

const int MOD = 1000000007;

int power(int x) {
    if (x == 0) return 1;
    if (x == 1) return 2;
    long long mid = power(x >> 1);
    mid = (mid * mid) % MOD;
    if (x & 1) return (mid * 2) % MOD;
    else return mid;
}

int main() {
    int n;
    while (cin >> n) {
        int res = power(p[n-1]);
        res = (res + MOD - 1) % MOD;
        cout << res << endl;
    }
    return 0;
}
