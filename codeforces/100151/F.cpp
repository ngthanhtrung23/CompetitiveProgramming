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

char s[22];

int nPrime, primes[300111];
bool good[4000111];

long long gcd(long long x, long long y) {
    if (!y) return x;
    return gcd(y, x % y);
}

void sieve() {
    FOR(i,2,2000) if (!good[i]) {
        int j = i * i;
        while (j <= 4000000) {
            good[j] = true;
            j += i;
        }
    }
    FOR(i,2,4000000)
    if (!good[i]) {
        primes[++nPrime] = i;
    }
}

int p[111], k[111], cnt;

void attempt(int i, long long prod, vector<long long> &res) {
    if (i > cnt) {
        res.push_back(prod);
        return ;
    }
    long long cur = 1;
    for(int power = 0; power <= k[i]; ++power, cur *= p[i]) {
        attempt(i+1, prod * cur, res);
    }
}

bool mark[11];
int match[333];

long long getRandom() {
    FOR(c,'a','z') match[c] = -1;
    memset(mark, false, sizeof mark);

    long long res = 0;
    vector<int> cand;

    REP(i,strlen(s)) {
        if (match[s[i]] == -1) {
            cand.clear();
            REP(x,10)
            if (i || x)
                if (!mark[x]) cand.push_back(x);

            int v = cand[rand() % cand.size()];
            mark[v] = true;
            match[s[i]] = v;
        }
        res = res * 10 + match[s[i]];
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    sieve();

    int ntest; scanf("%d\n", &ntest);
    srand(7777);
    FOR(test,1,ntest) {
        gets(s);

        long long g = 0;
        REP(turn,10000) {
            long long cur = getRandom();
            if (!turn) g = cur;
            else g = gcd(g, cur);
        }

        printf("Case %d:", test);
        vector<long long> res; res.clear();

        cnt = 0;
        for(int i = 1; primes[i] * primes[i] <= g; ++i) if (g % primes[i] == 0) {
            p[++cnt] = primes[i]; k[cnt] = 0;
            while (g % primes[i] == 0) {
                ++k[cnt];
                g /= primes[i];
            }
        }
        if (g > 1) {
            p[++cnt] = g; k[cnt] = 1;
        }

        attempt(1, 1, res);

        sort(res.begin(), res.end());
        REP(i,res.size()) {
            cout << ' ' << res[i];
        }
        puts("");
    }
    return 0;
}