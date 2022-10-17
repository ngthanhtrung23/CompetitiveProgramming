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
    int nRow, nCol, s; cin >> nRow >> nCol >> s;
    vector<vector<int>> a(nRow, vector<int> (nCol, 0));

    auto get_ids = [&] (int n) {
        vector<int> res(n);
        std::iota(res.begin(), res.end(), 0);
        return res;
    };

    for (auto& row : a) {
        for (int& x : row) cin >> x;
    }

    vector<int> a_ids = get_ids(nRow);
    vector<int> b_ids = a_ids;
    for (int i = 0; i < s; ++i) {
        int k; cin >> k;
        --k;
        std::stable_sort(b_ids.begin(), b_ids.end(), [&] (int r1, int r2) {
                return a[r1][k] < a[r2][k];
                });
    }

    if (a_ids == b_ids) {
        cout << 0 << endl;
        return;
    }

    vector<int> res;
    vector<int> ids = get_ids(nCol);

    do {
        auto cur = get_ids(nRow);
        REP(i,nCol) {
            int x = ids[i];
            std::stable_sort(cur.begin(), cur.end(), [&] (int r1, int r2) {
                    return a[r1][x] < a[r2][x];
                    });

            if (cur == b_ids) {
                vector<int> t { ids.begin(), ids.begin() + i + 1 };
                if (res.empty() || SZ(res) > i+1 || (SZ(res) == i+1 && res > t)) {
                    res = t;
                }
                break;
            }
        }
    } while (next_permutation(ids.begin(), ids.end()));

    cout << SZ(res) << '\n';
    for (int x : res) cout << 1+x << ' ';
    cout << endl;
}
