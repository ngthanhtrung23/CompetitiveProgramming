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

const int MN = 200111;

int it[MN * 3];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    it[i] = (r - l + 1);
    if (l == r) return ;
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
}

int kth(int i, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (it[CT(i)] >= k) return kth(CT(i), l, mid, k);
    else return kth(CP(i), mid+1, r, k - it[CT(i)]);
}

void remove(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    it[i]--;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    remove(CT(i), l, mid, u);
    remove(CP(i), mid+1, r, u);
}

int main() {
    int n; long long k;
    while (cin >> n >> k) {
        build(1, 1, n);
        FOR(i,1,n) {
            long long id = k + 1;
            if (id > n - i + 1) id = n - i + 1;
            k -= id-1;

            int x = kth(1, 1, n, id);
            printf("%d ", x);
            remove(1, 1, n, x);
        }
        puts("");
    }
    return 0;
}
