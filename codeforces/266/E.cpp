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
const int MN = 100111;

const long long MOD = 1000000007LL;

struct Node {
    long long val[6];
    int cover;
} it[MN * 6];

long long sumi[6][MN], a[MN], c[11][11];
int n, q;

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void down(int i, int l, int r, int mid) {
    if (it[i].cover < 0) return ;

    it[CT(i)].cover = it[i].cover;
    it[CP(i)].cover = it[i].cover;

    REP(t,6) {
        it[CT(i)].val[t] = it[i].cover * (sumi[t][mid] - sumi[t][l-1] + MOD) % MOD;
        it[CP(i)].val[t] = it[i].cover * (sumi[t][r] - sumi[t][mid] + MOD) % MOD;
    }

    it[i].cover = -1;
}

void cal(int i) {
    REP(t,6)
        it[i].val[t] = (it[CT(i)].val[t] + it[CP(i)].val[t]) % MOD;
}

void build(int i, int l, int r) {
    if (l == r) {
        REP(t,6) {
            it[i].val[t] = a[l] * (sumi[t][l] - sumi[t][l-1] + MOD) % MOD;
        }
        it[i].cover = -1;
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    cal(i);
    it[i].cover = -1;

    // cout << i << ' ' << l << ' ' << r << endl;
    // cout << "a = "; FOR(x,l,r) cout << a[x] << ' '; cout << endl;
    // PR0(it[i].val, 6);
}

void update(int i, int l, int r, int u, int v, int k) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].cover = k;
        REP(t,6) it[i].val[t] = k * (sumi[t][r] - sumi[t][l-1] + MOD) % MOD;
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    update(CT(i), l, mid, u, v, k);
    update(CP(i), mid+1, r, u, v, k);

    cal(i);
}

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long xx = x*x % MOD;
    if (k == 2) return xx;
    if (k == 3) return xx * x % MOD;
    if (k == 4) return xx * xx % MOD;
    return xx * xx % MOD * x % MOD;
}

long long get(int i, int l, int r, int u, int v, int k) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) {
        long long res = 0;

        REP(t,k+1) {
            res = (res + c[k][t] * it[i].val[t] % MOD * power((MOD + 1 - u) % MOD, k-t)) % MOD;
        }

        // cout << i << ' ' << l << ' ' << r << " --> " << res << endl;
        // PR0(it[i].val, 6);
        return res;
    }

    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    long long res = (get(CT(i), l, mid, u, v, k) + get(CP(i), mid+1, r, u, v, k)) % MOD;
    cal(i);
    return res;
}

int main() {
    REP(t,6) {
        FOR(i,1,100000) {
            sumi[t][i] = (sumi[t][i-1] + power(i, t)) % MOD;
        }
    }
    c[0][0] = 1;
    FOR(i,1,10) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
    }

    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) {
            int t; scanf("%d", &t);
            a[i] = t;
        }
        build(1,1,n);

        while (q--) {
            char c = '#';
            while (c != '=' && c != '?') scanf("%c", &c);
            if (c == '=') {
                int u, v, k; scanf("%d%d%d", &u, &v, &k);
                update(1, 1, n, u, v, k);
            }
            else {
                int u, v, k; scanf("%d%d%d", &u, &v, &k);
                printf("%d\n", (int) get(1, 1, n, u, v, k));
            }
        }
        // puts("---");
    }
    return 0;
}
