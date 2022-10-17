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
// Bipartite matching {{{
struct Matching {
    int n;
    vector< vector<int> > ke;
    vector< int > seen;
    vector< int > matchL, matchR;
    int iteration;

    Matching(int _n) : n(_n), ke(_n), seen(_n, false), matchL(_n, -1), matchR(_n, -1), iteration{0} {
    }

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool dfs(int u) {
        seen[u] = iteration;
        for (int v : ke[u]) {
            if (matchR[v] < 0) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u]) {
            if (seen[matchR[v]] != iteration && dfs(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match() {
        int res = 0;
        int newMatches = 0;
        do {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++) {
                if (matchL[u] < 0 && dfs(u)) ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};
// }}}

void solve() {
    int n;
    while (cin >> n) {
        int l = 0, r = 0;
        vector<pair<int,int>> lefts;
        map<pair<int,int>, int> ids_left, ids_right;
        REP(i,n) {
            int x, y; cin >> x >> y;
            if ((x + y) % 2 == 0) {
                lefts.emplace_back(x, y);
                ++l;
            } else {
                ids_right[make_pair(x, y)] = r++;
            }
        }
        Matching matching(max(l, r));
        REP(i,l) {
            auto [x, y] = lefts[i];
            vector<pair<int,int>> DIRS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto [dx, dy] : DIRS) {
                int x2 = x + dx;
                int y2 = y + dy;
                auto p = make_pair(x2, y2);
                if (ids_right.count(p)) {
                    matching.addEdge(i, ids_right[p]);
                }
            }
        }

        int res = matching.match();
        cout << n - res << endl;
    }
}
