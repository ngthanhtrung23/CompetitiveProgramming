#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
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

int p5[11];

int get(int x, int k) {
    return (x % p5[k+1]) / p5[k];
}

int set(int x, int k, int v) {
    return x - get(x, k) * p5[k] + v * p5[k];
}

int memo[33][70111];

int dp(int sum, int x) {
    if (memo[sum][x] >= 0) return memo[sum][x];
    REP(i,6)
    if (get(x, i) && sum + i + 1 <= 31) {
        int y = set(x, i, get(x, i)-1);
        if (dp(sum+i+1, y) == 0) {
            return memo[sum][x] = 1;
        }
    }
    return memo[sum][x] = 0;
}

char s[111];

int main() {
    memset(memo, -1, sizeof memo);
    p5[0] = 1;
    FOR(i,1,10) p5[i] = p5[i-1] * 5;
    
    while (gets(s)) {
        if (strlen(s) == 0) break;
        int now = p5[6] - 1;
        int sum = 0;
        cout << s << ' ';
        int turn = 0;
        REP(i,strlen(s)) {
            sum += s[i] - '0';
            if (sum > 31) {
                if (i % 2 == 0) cout << 'B' << endl;
                else cout << 'A' << endl;
                break;
            }
            now = set(now, s[i]-'1', get(now, s[i]-'1') - 1);
            turn = 1 - turn;
        }
        if (sum > 31) continue;
        if (!now) break;
        if ((dp(sum, now) + turn) % 2) cout << 'A' << endl;
        else cout << 'B' << endl;
    }
    return 0;
}
