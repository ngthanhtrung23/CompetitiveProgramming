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
// DisjointSet {{{
struct DSU {
    vector<int> lab;

    DSU(int n) : lab(n+1, -1) {}

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }

    bool same_component(int u, int v) {
        return getRoot(u) == getRoot(v);
    }

    int component_size(int u) {
        return -lab[getRoot(u)];
    }
};
// }}}
// Biconnected Component {{{
struct BiconnectedComponent {
    int n;
    vector<vector<int>> g;
    vector<int> low, num, s;
    vector< vector<int> > components;
    int counter;

    BiconnectedComponent(int _n, const vector<vector<int>>& _g) : n(_n), g(_g), low(n, -1), num(n, -1), counter(0) {
        for (int i = 0; i < n; i++)
            if (num[i] < 0)
                dfs(i, 1);
    }

    void dfs(int x, int isRoot) {
        low[x] = num[x] = ++counter;
        if (g[x].empty()) {
            components.push_back(vector<int>(1, x));
            return;
        }
        s.push_back(x);

        for (int i = 0; i < (int) g[x].size(); i++) {
            int y = g[x][i];
            if (num[y] > -1) low[x] = min(low[x], num[y]);
            else {
                dfs(y, 0);
                low[x] = min(low[x], low[y]);

                if (isRoot || low[y] >= num[x]) {
                    components.push_back(vector<int>(1, x));
                    while (1) {
                        int u = s.back();
                        s.pop_back();
                        components.back().push_back(u);
                        if (u == y) break;
                    }
                }
            }
        }
    }
};
// }}}

const std::vector<std::pair<int,int>> DIRECTIONS = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void solve() {
    int nRow, nCol; cin >> nRow >> nCol;
    vector<string> board(nRow);
    for (auto& row : board) cin >> row;

    auto id = [&] (int r, int c) { return r * nCol + c; };
    auto isInside = [&] (int r, int c) {
        return 0 <= r && r < nRow
            && 0 <= c && c < nCol;
    };
    vector<vector<int>> g(nRow * nCol);
    DSU dsu(nRow * nCol);

    int nEmpty = 0;
    for (int r = 0; r < nRow; ++r) {
        for (int c = 0; c < nCol; ++c) {
            if (board[r][c] == '#') continue;
            ++nEmpty;

            for (auto [dr, dc] : DIRECTIONS) {
                int rr = r + dr;
                int cc = c + dc;
                if (!isInside(rr, cc) || board[rr][cc] == '#') continue;

                int u = id(r, c);
                int v = id(rr, cc);
                g[u].push_back(v);
                dsu.merge(u, v);
            }
        }
    }
    BiconnectedComponent bicomp(nRow * nCol, g);
    int nPairs = nEmpty * (nEmpty - 1);
    int goodPairs = 0;
    for (const auto& comp : bicomp.components) {
        goodPairs += SZ(comp) * (SZ(comp) - 1);
    }

    cout << nPairs - goodPairs << endl;
}
