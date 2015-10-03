#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 200111;

int a[MN], n;
int max_rem[MN], good[MN*2];
int x[MN];
int cache_gcd[MN];

ll get(int d) {
    memset(max_rem, 0, sizeof max_rem);
    FOR(i,1,n) max_rem[ i % d] = max(max_rem[i % d], a[i]);
//    cout << d << endl;
//    PR0(max_rem, d);

    int allGood = 1;
    FOR(i,1,n) {
        good[i] = a[i] == max_rem[i % d];
        if (!good[i]) allGood = 0;
    }
//    PR(good, n);

    FOR(i,n+1,n+n) good[i] = good[i-n];

    if (allGood) {
        ll res = 0;
        FOR(len,1,n-1)
            if (cache_gcd[len] == d) {
                res += n;
            }
        return res;
    }

    int start = 0;
    FOR(i,1,n) if (!good[i]) {
        start = i;
        break;
    }

    int i = start;
    memset(x, 0, sizeof x);
    while (i < start+n) {
        if (!good[i]) ++i;
        else {
            int j = i;
            while (j < n+n && good[j+1]) ++j;

            x[j - i + 1] ++;

            i = j + 1;
        }
    }

    ll res = 0;
    FORD(i,n-2,1) x[i] += x[i+1];
    FORD(i,n-2,1) x[i] += x[i+1];

    FOR(len,1,n-1)
        if (cache_gcd[len] == d) {
            res += x[len];
        }
    return res;
}

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

int main() {
    GN(n);
    FOR(i,1,n) GN(a[i]);

    FOR(i,1,n) cache_gcd[i] = __gcd(i, n);

//        DEBUG(n);

    ll res = 0;
    for(int d = 1; d*d <= n; ++d) if (n % d == 0) {
        if (d != n) res += get(d);

        if (d*d != n && d != 1) res += get(n/d);
    }
    cout << res << endl;
//        cout << "----" << endl;
}
