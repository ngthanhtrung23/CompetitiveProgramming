/**
 * Let s1 and s2 be the 2 answer strings.
 * Answer is one of (s1, s2, !s1, !s2). Why?
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
#define TWO(X) (1LL<<(X))

int bit(int mask, int i) {
    return (mask >> i) & 1LL;
}
int correct(int mask, int ans, int l, int r) {
    int res = 0;
    for (int i = l; i <= r; i++) {
        if (bit(mask, i) == bit(ans, i)) ++res;
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, q; cin >> n >> q;
        if (q > 40) continue;

        vector<int> ans(n), scores(n);
        REP(i,n) {
            string s; cin >> s;
            REP(j,q) {
                if (s[j] == 'T') {
                    ans[i] += TWO(j);
                }
            }
            cin >> scores[i];

            if (scores[i] < q - scores[i]) {
                scores[i] = q - scores[i];
                ans[i] = TWO(q) - 1 - ans[i];
            }
        }
        if (n == 1) {
            n = 2;
            ans.push_back(ans[0]);
            scores.push_back(scores[0]);
        }

        // PR0(ans, n);
        // PR0(scores, n);
        pair<int, int> best_correct = {-1, 0};
        // update best using answers
        REP(i,n) {
            best_correct = max(best_correct, {scores[i], ans[i]});
        }

        cout << "Case #" << test << ": ";
        REP(i,q) {
            if ((best_correct.second >> i) & 1) cout << 'T';
            else cout << 'F';
        }
        cout << ' ';
        int tu = best_correct.first;
        int mau = 1;
        int g = __gcd(tu, mau);
        tu /= g;
        mau /= g;
        cout << tu << '/' << mau << '\n';
    }
    return 0;
}

