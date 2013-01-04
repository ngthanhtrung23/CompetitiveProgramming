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
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
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

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

long long lcm(long long a, long long b) {
    return a * b / gcd(a, b);
}

const int MN = 1000111;

long long a, b, k, l;
int d[MN], qu[MN], first, last;

void bfs(int start) {
    qu[first = last = 1] = start;
    memset(d, -1, sizeof d);
    d[start] = 0;

    while (first <= last) {
        int u = qu[first++];
        FOR(x,1,k) {
            int v;
            if (x == 1) v = u - 1;
            else v = u - u % x;
            if (d[v] < 0) {
                d[v] = d[u] + 1;
                qu[++last] = v;
            }
        }
    }
    // PR0(d, l+1);
}

int main() {
    while (cin >> a >> b >> k) {
        l = 1;
        FOR(i,1,k) l = lcm(i, l);
        // DEBUG(l);

        bfs(l);

        if (a % l == 0 && b % l == 0) {
            long long need = (a - b) / l;
            cout << need * d[0] << endl;
        }
        else if (a / l == b / l) {
            a = a % l;
            b = b % l;
            bfs(a);
            cout << d[b] << endl;
        }
        else {
            long long aa = a - a % l;
            long long bb = b - b % l + l;

            long long need = (aa - bb) / l;
            long long res = need * d[0];
            res += d[b % l];

            bfs(a % l);
            res += d[0];

            cout << res << endl;
        }
    }
    return 0;
}
