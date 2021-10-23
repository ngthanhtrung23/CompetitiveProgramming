// Statement:
// - s: correct bracket seq
// - q queries:
//   - flip pi
//   - find ai: if flip ai -> correct bracket seq
//   - flip ai
//
// Idea:
// - can flip pi --> solution always exists
// - ( = +1, ) = -1
//   - correct bracket seq:
//     1. left -> right, prefix sum >= 0
//     2. at end of string, prefix sum == 0
//
// - flip ( -> )
//   ((())) -> (()))) -> ai = pi = 3
//   ()()() -> (())() -> ai = 2
//   --> ai = position of first )
//
// - flip ) -> (
//   --> ai = first position (
//   prefix sum(ai) >= 2
//   prefix sum(ai + 1) >= 2
//   prefix sum(ai + 2) >= 2
//   ...

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

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

char s[1000111];
int n, q;

int nn[4000111], lazy[4000111];
int pref[1000111];

void init(int i, int l, int r) {
    if (l == r) {
        nn[i] = pref[l];
        return;
    }
    int mid = (l + r) / 2;
    init(i*2, l, mid);
    init(i*2+1, mid+1, r);

    nn[i] = nn[i*2];
    if (nn[i*2+1] < nn[i]) {
        nn[i] = nn[i*2+1];
    }
}

void down(int i) {
    if (!lazy[i]) return;

    lazy[i*2] += lazy[i];
    lazy[i*2+1] += lazy[i];

    nn[i*2] += lazy[i];
    nn[i*2+1] += lazy[i];

    lazy[i] = 0;
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return;
    if (u <= l && r <= v) {
        nn[i] += val;
        lazy[i] += val;
        return;
    }
    down(i);

    int mid = (l + r) / 2;
    update(i*2, l, mid, u, v, val);
    update(i*2+1, mid+1, r, u, v, val);

    nn[i] = nn[i*2];
    if (nn[i*2+1] < nn[i]) {
        nn[i] = nn[i*2+1];
    }
}

int get(int i, int l, int r) {
    if (l == r) {
        if (nn[i] >= 2) {
            return l;
        } else {
            return n + 1;
        }
    }

    down(i);

    int mid = (l + r) / 2;

    if (nn[i*2+1] < 2) {
        return get(i*2+1, mid+1, r);
    } else {
        int leftChild = get(i*2, l, mid);
        if (leftChild == n+1) return mid+1;
        else return leftChild;
    }
}

struct DS {
    DS() {
        FOR(i,1,n) {
            if (s[i] == ')') {
                close.push(i);
            }
        }

        // pref
        FOR(i,1,n) {
            pref[i] = pref[i-1];
            if (s[i] == '(') pref[i]++;
            else pref[i]--;
        }
        init(1, 1, n);
    }

    void flip(int x) {
        s[x] = '(' + ')' - s[x];
        if (s[x] == ')') {
            // ( -> )
            close.push(x);
            update(1, 1, n, x, n, -2);
        } else {
            // ) -> (
            // close.erase(x);  // priority queue cannot erase
            update(1, 1, n, x, n, +2);
        }
    }

    int findFirstClose() {
        while (true) {
            int x = close.top();
            if (s[x] == '(') close.pop();
            else return x;
        }
    }

    int findFirstOpen() {
        return get(1, 1, n);
    }

    priority_queue<int, std::vector<int>, std::greater<int>> close;
};

int32_t main() {
    GN(n); GN(q);
    FOR(i,1,n) {
        while (s[i] != '(' && s[i] != ')') {
            GETCHAR(s[i]);
        }
        assert(s[i] == '(' || s[i] == ')');
    }
    DS ds;

    while (q--) {
        int p; GN(p);

        // flip p
        ds.flip(p);

        // find a
        int res = -1;
        if (s[p] == ')') {
            // ( -> )
            // --> res = position of first )
            res = ds.findFirstClose();
        } else {
            assert(s[p] == '(');
            // ) -> (
            res = ds.findFirstOpen();
        }

        // flip a
        ds.flip(res);

        printf("%d ", res);
    }
    puts("");
    return 0;
}
