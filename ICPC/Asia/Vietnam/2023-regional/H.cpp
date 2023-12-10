// template {{{
#include "bits/stdc++.h"
using namespace std;

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

mt19937_64 rng(58);
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

const string B64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char B64_TO_DIGIT[300];

const int MN = 5011;
int8_t a[MN][MN];

struct Hash : pair<int, uint64_t> {
    void reset() {
        first = 0;
        second = 0;
    }

    void add(int8_t x) {
        first += x;
        second = second * 3 + x + 1;
    }
};
Hash hashRow[MN];

void solve() {
    for (int i = 0; i < 64; ++i) {
        B64_TO_DIGIT[B64[i]] = i;
    }

    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        string s; cin >> s;

        auto to_rc = [&] (int id) { return make_pair(id / n, id % n); };
        for (int i = 0; i < n; ++i) hashRow[i].reset();

        for (int i = 0; i < SZ(s); ++i) {
            int digit = B64_TO_DIGIT[s[i]];
            for (int bit = 0; bit < 6; ++bit) {
                int id = i*6 + bit;
                if (id >= n*n) continue;
                auto [r, c] = to_rc(id);
                a[r][c] = (digit >> bit) & 1;
                hashRow[r].add(a[r][c]);
            }
        }
        try {
            for (int j = 0; j < n; ++j) {
                // Find 2 rows i1, i2:
                // - hashRow[i1] != hashRow[i2]
                // - a[i1][j] == a[i2][j] == 0
                int i1 = -1, i2 = -1;
                for (int i = 0; i < n; ++i) {
                    if (a[i][j] == 0) {
                        if (i1 < 0) i1 = i;
                        else if (hashRow[i] != hashRow[i1]) {
                            i2 = i;
                            for (int j2 = 0; j2 < n; ++j2) {
                                if (a[i1][j2] != a[i2][j2]) {
                                    cout << "YES\n";
                                    cout << 1+i1 << ' ' << 1+j << ' '
                                        << 1+i2 << ' ' << 1+j2 << '\n';
                                    throw 1;
                                }
                            }
                        }
                    }
                }
            }
            cout << "NO\n";
        } catch (...) {
        }
    }
}
