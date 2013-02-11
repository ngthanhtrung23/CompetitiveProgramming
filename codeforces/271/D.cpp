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
const long long MOD = 1000000007;

typedef pair<ll, ll> Hash;

Hash operator - (const Hash &a, const Hash &b) {
    return MP(a.F - b.F, (a.S - b.S + MOD) % MOD);
}

Hash operator + (const Hash &a, const Hash &b) {
    return MP(a.F + b.F, (a.S + b.S) % MOD);
}

Hash operator * (const Hash &a, int k) {
    return MP(a.F * k, (a.S * k) % MOD);
}

Hash operator * (const Hash &a, const Hash &b) {
    return MP(a.F * b.F, (a.S * b.S) % MOD);
}

set< Hash > s;

char a[2011];
char good[300];
int k, l;
Hash h[2011];
Hash p[2011];

Hash getHash(int i, int j) {
    Hash cur = (i == 0) ? h[j] : h[j] - h[i-1];
    return cur * p[l - i];
}

int main() {
    p[0] = MP(1,1);
    FOR(i,1,2000) p[i] = p[i-1] * 31;

    while (gets(a)) {
        s.clear();
        FOR(c,'a','z') scanf("%c", &good[c]);
        scanf("%d\n", &k);

        l = strlen(a);

        REP(i,l) {
            if (i == 0) {
                h[i] = MP(a[i] - 'a' + 1, a[i] - 'a' + 1);
            }
            else {
                h[i] = h[i-1] + MP(a[i] - 'a' + 1, a[i] - 'a' + 1) * p[i];
            }
        }
        REP(start,l) {
            int now = 0;

            FOR(last,start,l-1) {
                if (good[a[last]] == '0') ++now;
                if (now > k) break;

                s.insert(getHash(start, last));
            }
        }
        cout << s.size() << endl;
    }
    return 0;
}
