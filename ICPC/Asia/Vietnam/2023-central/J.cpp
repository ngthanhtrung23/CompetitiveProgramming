// template {{{
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define I(x) int x; cin >> x;
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))
#define ALL(s) (s).begin(), (s).end()

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {
    return uniform_int_distribution<long long> (l, r)(rng);
}

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (int& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    srand(7777);
    solve();
    return 0;
}

// }}}
// KMP {{{
template<typename Container>
std::vector<int> prefix_function(const Container& s) {
    int n = s.size();
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

// Tested: https://oj.vnoi.info/problem/substr
// Return all positions (0-based) that pattern `pat` appears in `text`
std::vector<int> kmp(const std::string& pat, const std::string& text) {
    auto pi = prefix_function(pat + '\0' + text);
    std::vector<int> res;
    for (size_t i = pi.size() - text.size(); i < pi.size(); ++i) {
        if (pi[i] == (int) pat.size()) {
            res.push_back(i - 2 * pat.size());
        }
    }
    return res;
}

// Tested: https://oj.vnoi.info/problem/icpc22_mt_b
// Returns cnt[i] = # occurrences of prefix of length-i
// NOTE: cnt[0] = n+1 (0-length prefix appears n+1 times)
std::vector<int> prefix_occurrences(const string& s) {
    int n = s.size();
    auto pi = prefix_function(s);
    std::vector<int> res(n + 1);
    for (int i = 0; i < n; ++i) res[pi[i]]++;
    for (int i = n-1; i > 0; --i) res[pi[i-1]] += res[i];
    for (int i = 0; i <= n; ++i) res[i]++;
    return res;
}
// }}}

void solve() {
    int n, patLen, eachPat; cin >> n >> patLen >> eachPat;
    vector<int> costRed(n + 1), costBlue(n + 1);
    for (int i = 1; i <= n; ++i) cin >> costRed[i];
    for (int i = 1; i <= n; ++i) cin >> costBlue[i];
    string s; cin >> s;
    auto pref = prefix_function(s);

    int res = -2000111000;
    for (int trace = 0; trace <= 1; ++trace) {
        int usedRed = 0, usedBlue = 0, matched = -1;
        for (int pat = 0; pat <= n; ++pat) { // how many times pattern appear
            int scores = pat * eachPat;
            for (int totalRed = usedRed; totalRed <= n - usedBlue; ++totalRed) {
                int totalBlue = n - totalRed;
                int cur = scores - costRed[totalRed] - costBlue[totalBlue];

                if (trace == 0) {
                    res = max(res, cur);
                } else if (trace == 1 && res == cur) {
                    string result = "";
                    for (int i = 1; i <= pat; ++i) {
                        if (i == 1) {
                            result += s;
                        } else {
                            for (int j = pref[patLen - 1]; j < patLen; ++j) {
                                result += s[j];
                            }
                        }
                    }
                    for (int r = 1; r <= totalRed - usedRed; ++r) result += 'R';
                    for (int b = 1; b <= totalBlue - usedBlue; ++b) result += 'B';
                    cout << result << endl;
                    return;
                }
            }
            // match one more time
            for (int i = matched + 1; i < patLen; ++i) {
                usedRed += s[i] == 'R';
                usedBlue += s[i] == 'B';
            }
            matched = pref[patLen-1] - 1;
            if (usedRed + usedBlue > n) break;
        }
        if (trace == 0) cout << res << endl;
    }
}
