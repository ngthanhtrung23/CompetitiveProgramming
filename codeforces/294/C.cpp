#define _GLIBCXX_DEBUG
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
const long long MOD = 1000000007LL;

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long u = power(x, k >> 1);
    u = (u * u) % MOD;

    if (k & 1) return (u * x) % MOD;
    else return u;
}

int n, m;
bool mark[1011];
vector<int> x;
long long gt[1011], revgt[1011], p2[1011];

void solve(int first, int last) {
    gt[0] = 1; p2[0] = 1;
    FOR(i,1,1000) {
        gt[i] = (gt[i-1] * i) % MOD;
        p2[i] = (p2[i-1] * 2) % MOD;
    }
    FOR(i,0,1000) revgt[i] = power(gt[i], MOD - 2);

    long long res = gt[n - m];
    res = (res * revgt[first]) % MOD;
    res = (res * revgt[last]) % MOD;

    REP(i,x.size()) {
        int u = x[i];
        res = (res * revgt[u]) % MOD;
        res = res * p2[u - 1] % MOD;
    }
    printf("%d\n", (int) res);
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        memset(mark, false, sizeof mark);
        FOR(i,1,m) {
            int u; scanf("%d", &u);
            mark[u] = true;
        }
        int last = 0, first = 0;
        int i = 1;
        while (!mark[i]) {
            ++i;
        }
        first = i - 1;
        i = n;
        while (!mark[i]) {
            --i;
        }
        last = n - i;

        // DEBUG(first);
        // DEBUG(last);

        i = first + 1;
        x.clear();
        while (i <= n) {
            if (mark[i]) ++i;
            else {
                int j = i;
                while (j < n && !mark[j+1]) ++j;
                if (j != n) x.push_back(j - i + 1);
                i = j + 1;
            }
        }
        solve(first, last);
    }
    return 0;
}
