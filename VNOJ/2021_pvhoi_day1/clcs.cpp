// binary search:
// - kiem tra xem kq >= m hay khong?
// - f[i][j] = 1 iff a[i][j] >= m
// --> 1 bang con co median >= m <=> sum(f) >= h*w/2+1
//
// --> O(r*c*log)

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

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

const int MN = 3011;
int a[MN][MN];
int f[MN][MN];
int nRow, nCol, needRow, needCol, need;

int getSum(int i1, int j1, int i2, int j2) {
    return f[i2][j2]
        - f[i1-1][j2]
        - f[i2][j1-1]
        + f[i1-1][j1-1];
}

bool check(int val) {
    // init f
    FOR(i,1,nRow) FOR(j,1,nCol) {
        f[i][j] = a[i][j] >= val;

        // accumulate
        f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1] + f[i][j];
    }

    // loop through all submatrices
    for (int i1 = 1, i2 = needRow; i2 <= nRow; i1++, i2++) {
        for (int j1 = 1, j2 = needCol; j2 <= nCol; j1++, j2++) {
            if (getSum(i1, j1, i2, j2) >= need) {
                return true;
            }
        }
    }
    return false;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    GN(nRow); GN(nCol);
    GN(needRow); GN(needCol);

    FOR(i,1,nRow) FOR(j,1,nCol) {
        GN(a[i][j]);
    }

    need = needRow * needCol / 2 + 1;

    // binary search
    // - find largest m: there exists submatrix sum(f) >= need;
    int l = 1, r = nRow * nCol, res = 1;
    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res << endl;
    return 0;
}
