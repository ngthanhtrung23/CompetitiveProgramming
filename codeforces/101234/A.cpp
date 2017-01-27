#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
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

const int MN = 100111;

struct Node {
    int sum;
    int all;

    void fill(int val, int l, int r) {
        all = val;
        sum = val * (r - l + 1);
    }
} it[MN * 4];

void down(int i, int l, int r, int mid) {
    if (it[i].all >= 0) {
        int t = it[i].all; it[i].all = -1;

        it[i<<1].fill(t, l, mid);
        it[i<<1|1].fill(t, mid+1, r);
    }
}

void up(int i) {
    it[i].sum = it[i<<1].sum + it[i<<1|1].sum;
}

int a[MN];
pair<int,int> queries[MN];

void build(int i, int l, int r, int val) {
    it[i].all = -1;

    if (l == r) {
        it[i].sum = (a[l] >= val);
        return ;
    }

    int mid = (l + r) >> 1;
    build(i<<1, l, mid, val);
    build(i<<1|1, mid+1, r, val);
    up(i);
}

int getSum(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;

    int mid = (l + r) >> 1;
    down(i, l, r, mid);
    int res = getSum(i<<1, l, mid, u, v)
        + getSum(i<<1|1, mid+1, r, u, v);
    up(i);

    return res;
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].fill(val, l, r);
        return ;
    }
    int mid = (l + r) >> 1;

    down(i, l, r, mid);
    update(i<<1, l, mid, u, v, val);
    update(i<<1|1, mid+1, r, u, v, val);
    up(i);
}

int n, q;
bool check(int val) {
    // check if middle element >= val

    build(1, 1, n, val);

    FOR(i,1,q) {
        int l = queries[i].first, r = queries[i].second;
        int s = getSum(1, 1, n, min(l, r), max(l, r));

        if (l <= r) {
            update(1, 1, n, l, r-s, 0);
            update(1, 1, n, r-s+1, r, 1);
        }
        else {
            swap(l, r);
            update(1, 1, n, l, l+s-1, 1);
            update(1, 1, n, l+s, r, 0);
        }
    }
    int mid = (n + 1) / 2;
    return getSum(1, 1, n, mid, mid);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    GN(n); GN(q);
    FOR(i,1,n) GN(a[i]);
    FOR(i,1,q) {
        GN(queries[i].first);
        GN(queries[i].second);
    }

    int l = 1, r = n, res = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", res);
}
