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

void solve() {
    int nRow, nCol, nBombs;
    cin >> nRow >> nCol >> nBombs;
    vector<string> board(nRow);
    for (auto& row : board) cin >> row;

    // extract row segments of the board (by splitting each row at walls).
    // for each segments, segs contains positions of enemies. As a tiny
    // optimization, we try to skip segments that are empty.
    vector<vector<int>> segs;
    for (const string& row : board) {
        vector<int> cur;
        for (int i = 0; i < nCol; ++i) {
            if (row[i] == 'x') cur.push_back(i);
            else if (row[i] == '#' && !cur.empty()) {
                segs.push_back(cur);
                cur.clear();
            }
        }
        if (!cur.empty()) segs.push_back(cur);
    }

    // returns true if we can kill all enemies given a value V
    auto check = [&] (int V) {
        int need = 0;  // how many bombs do we actually need?
        for (const auto& seg : segs) {
            int last = -1;
            for (int pos : seg) {
                if (last < pos) {
                    ++need;
                    last = pos + 2*V;
                }
            }
        }
        return need <= nBombs;
    };

    // binary search to find minimum V
    int l = 0, r = nCol, res = nCol + 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    if (res > nCol) res = -1;
    cout << res << endl;
}
