/**
 * sum(group A) = prod(group B)
 * --> group B has at most 60 numbers
 * --> sum(group B) does not exceed 30k
 * --> sum(group A) in [sum_all_numbers - 30k, sum_all_numbers]
 * --> brute force sum(group A)
 */

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
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
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n; cin >> n;
        vector<int> p(n), cnt(n);
        int sum_all = 0;
        REP(i,n) {
            cin >> p[i] >> cnt[i];
            sum_all += p[i] * cnt[i];
        }

        int res = 0;
        FOR(prod,max(0LL, sum_all-30000),sum_all) {
            int u = prod;
            vector<int> new_cnt = cnt;

            REP(i,n) {
                while (new_cnt[i] > 0 && u % p[i] == 0) {
                    new_cnt[i]--;
                    u /= p[i];
                }
            }

            if (u == 1) {
                int sum = 0;
                REP(i,n) sum += p[i] * new_cnt[i];

                if (sum == prod) res = prod;
            }
        }
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
