#include "bits/stdc++.h"
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

const int MN = 1e5 + 11;
const int MOD = 1e9 + 7;
int fact[MN], inv_fact[MN];

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    int mid = power(x, k / 2);
    mid = mid * mid % MOD;

    if (k % 2) return (mid * x) % MOD;
    return mid;
}

int inverse(int x) {
    return power(x, MOD - 2);
}

int C(int n, int k) {
    if (k > n) return 0;

    assert(0 <= k && k <= n && n < MN);
    return fact[n] * inv_fact[n-k] % MOD;
}

int32_t main() {
    ios::sync_with_stdio(0);

    fact[0] = 1;
    FOR(i,1,MN-1) fact[i] = fact[i-1] * i % MOD;
    REP(i,MN) {
        inv_fact[i] = inverse(fact[i]);
        assert(fact[i] * inv_fact[i] % MOD == 1);
    }

    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        vector<int> lens(n);
        for (int& len : lens) {
            cin >> len;
        }
        int n_dict; cin >> n_dict;
        vector<string> dict(n_dict);
        map< pair<int, char>, int > cnt;

        for (auto& word : dict) {
            cin >> word;
            cnt[make_pair(word.length(), word[0])]++;
        }

        int res = 0;
        for (const auto& word : dict) {
            if (SZ(word) != n) continue;
            cnt[make_pair(word.length(), word[0])]--;

            map< pair<int, char>, int > need;
            REP(i,n) {
                need[make_pair(lens[i], word[i])]++;
            }

            int cur = 1;
            for (auto [key, val] : need) {
                cur = cur * C(cnt[key], val) % MOD;
            }
            res = (res + cur) % MOD;

            cnt[make_pair(word.length(), word[0])]++;
        }
        cout << res << '\n';
    }
}
