// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

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

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
// }}}

void solve() {
    int N, nCol, first, last;
    while (cin >> N >> nCol >> first >> last) {
        --first; --last;

        auto get = [&] (int x) {
            return make_pair(x / nCol, x % nCol);
        };

        vector<tuple<int,int,int,int>> res;

        {
            auto [r1, c1] = get(first);
            auto [r2, c2] = get(last);
            if (last == N-1) c2 = nCol-1;

            if (r1 == r2) {
                res = {
                    {r1, c1, r2, c2},
                };
            } else if (r1 + 1 == r2) {
                if (c1 == 0 && c2 == nCol-1) {
                    res = {
                        {r1, 0, r2, nCol-1},
                    };
                } else {
                    res = {
                        {r1, c1, r1, nCol-1},
                        {r2, 0, r2, c2},
                    };
                }
            } else {
                if (c1 == 0 && c2 == nCol-1) {
                    res = {
                        {r1, 0, r2, nCol-1},
                    };
                } else if (c1 == 0) {
                    res = {
                        {r1, 0, r2-1, nCol-1},
                        {r2, 0, r2, c2},
                    };
                } else if (c2 == nCol-1) {
                    res = {
                        {r1, c1, r1, nCol-1},
                        {r1+1, 0, r2, nCol-1},
                    };
                } else if (c2 + 1 == c1) {
                    res = {
                        {r1, c1, r2-1, nCol-1},
                        {r1+1, 0, r2, c2},
                    };
                } else {
                    res = {
                        {r1, c1, r1, nCol-1},
                        {r1+1, 0, r2-1, nCol-1},
                        {r2, 0, r2, c2},
                    };
                }
            }
        }

        cout << res.size() << endl;
        for (auto [r1, c1, r2, c2] : res) {
            cout << c1 << ' ' << r1 << ' ' << c2 + 1 << ' ' << r2 + 1 << endl;
        }
    }
}
