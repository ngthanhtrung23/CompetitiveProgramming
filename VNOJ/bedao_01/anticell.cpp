// 1 1 1   1   1 1 1 1
// 1 1 1   1
// 1 1    11
//
//
// f(i, s): O(N*log(max sum)) state
// f(i, s):
// - s= a[i] --> f(i, s) = 1
// - = 0 if f(i, s/2) = 0
// - f(i, s) = sum(f(j, x)), sum(j+1 -> i) = s
//
//
// 1 1 1 1
// f(1, 1) = 1
//
// f(2, 1) = 1
// f(2, 2) = 1
//
// f(3, 1) = sum(f(2, x)) = 2
// f(3, 2) = sum(f(1, x)) = 1
//
// f(4, 1) = sum(f(3, x)) = 3
// f(4, 2) = sum(f(2, x)) = 2
// f(4, 4) = sum(f(0, x)) = 1

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

const int MN = 2000111;
int sumf[MN], a[MN], s[MN];
const int MOD = (int) (1e9 + 7);

set<int> can[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n; cin >> n;
    s[0] = 0;
    FOR(i,1,n) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }

    map<int, int> sum_to_id;
    FOR(i,0,n) sum_to_id[s[i]] = i;

    // PR(s, n);

    sumf[0] = 1;
    FOR(i,1,n) {
        int cur_sum = a[i];
        int j = i - 1; // j+1 -> i = cur_sum
        int f = sumf[j];
        can[i].insert(cur_sum);

        while (true) {
            // find: k
            // cur_sum = sum(a[j+1] .. a[i])
            //
            // sum(k+1 -> j) = cur_sum
            // s[j] - s[k] = cur_sum
            // s[k] = s[j] - cur_sum

            if (sum_to_id.count(s[j] - cur_sum) && can[j].count(cur_sum)) {
                j = sum_to_id[s[j] - cur_sum]; // sum(k+1 -> j) = cur_sum
                // now sum(j+1 -> i) = 2*cur_sum

                f = (f + sumf[j]) % MOD;
                cur_sum *= 2;
                can[i].insert(cur_sum);
            } else {
                break;
            }
        }
        sumf[i] = f;
    }
    cout << sumf[n] << endl;
    return 0;
}
