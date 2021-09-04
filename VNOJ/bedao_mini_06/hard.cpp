// - No "1" -> NO
//
// 1
// 1, 1
// 1, 2
// 1, 1, 2
// 1, 1, 3
// 1, 2, 3
//
//
// 1 -> s
//    <= s + 1

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

int32_t main() {
    int q; GN(q);
    set<int> all;
    while (q--) {
        int typ, val; GN(typ); GN(val);

        if (typ == 1) {
            if (all.count(val)) all.erase(val);
            else all.insert(val);
        } else {
            if (!all.count(1)) {
                puts("-1");
                continue;
            }

            int cur_sum = 0;
            int res = 0;
            while (cur_sum < val) {
                // find largest number, <= cur_sum + 1
                auto it = all.upper_bound(cur_sum + 1);
                auto cur = *prev(it);

                // next_sum >= x
                // OR next_sum >= all.upper_bound(cur_sum + 1) - 1
                int next_sum = val;
                if (it != all.end()) {
                    next_sum = min(next_sum, (*it) - 1);
                }

                // cur_sum + cnt * cur >= next_sum
                // cnt = (next_sum - cur_sum) / cur
                int cnt = (next_sum - cur_sum) / cur;
                if (cur_sum + cnt * cur < next_sum) ++cnt;

                res += cnt;
                cur_sum += cnt * cur;
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}
