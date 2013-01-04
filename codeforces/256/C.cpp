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

int nSeg;
struct Segment {
    long long l, r;
    long long value;
} a[100111];

long long get(long long n) {
    long long lb = ceil(sqrt(sqrt((long double) n)) - 1e-6);
    long long ub = floor(sqrt((long double) n) + 1e-6);

    set<long long> s;
    s.clear();

    FOR(i,1,nSeg) {
        if (a[i].r < lb || a[i].l > ub) continue;
        s.insert(a[i].value);
    }
    long long res = 0;
    while (s.find(res) != s.end()) ++res;
    return res;
}

void add(long long l, long long r, long long value) {
    ++nSeg;
    a[nSeg].l = l;
    a[nSeg].r = r;
    a[nSeg].value = value;
}

void init() {
    add(1, 3, 0);
    add(4, 15, 1);
    add(16, 81, 2);
    add(82, 6723, 0);
    add(6724, 50625, 3);
    add(50626, 1000000, 1);

    return ;

    FOR(i,4,1000000) {
        long long f = get(i);
        if (f == a[nSeg].value) {
            ++a[nSeg].r;
        }
        else {
            ++nSeg;
            a[nSeg].l = a[nSeg].r = i;
            a[nSeg].value = f;
        }
    }
    return ;
    FOR(i,1,nSeg) {
        cout << a[i].l << ' ' << a[i].r << ' ' << a[i].value << endl;
    }
}

long long sq4(long long n) {
    long long x = (long long) sqrt(sqrt((long double) n));
    x += 10;
    while (x*x*x*x >= n) --x;
    ++x;
    return x;
}

long long sq2(long long n) {
    long long x = (long long) sqrt((long double) n);
    x -= 10;
    while (x*x <= n) ++x;
    --x;
    return x;
}

long long get2(long long n) {
    FOR(i,1,nSeg)
        if (a[i].l <= n && n <= a[i].r)
            return a[i].value;
    long long lb = sq4(n);
    long long ub = sq2(n);

    set<long long> s;
    s.clear();

    FOR(i,1,nSeg) {
        if (a[i].r < lb || a[i].l > ub) continue;
        s.insert(a[i].value);
    }

    long long res = 0;
    while (s.find(res) != s.end()) ++res;
    return res;
}

int main() {
    init();
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        long long sum = 0;
        FOR(i,1,n) {
            long long a; cin >> a;
            sum ^= get2(a);
        }
        if (sum) puts("Furlo");
        else puts("Rublo");
    }
    return 0;
}
