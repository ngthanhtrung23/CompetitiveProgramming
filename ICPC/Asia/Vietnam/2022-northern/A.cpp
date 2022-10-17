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

map< pair<int,int>, int > VERTICES_TO_EDGE_ID = {
    {{1, 2}, 0},
    {{1, 3}, 1},
    {{2, 3}, 2},

    {{2, 4}, 3},
    {{2, 5}, 4},
    {{4, 5}, 5},

    {{3, 5}, 6},
    {{3, 6}, 7},
    {{5, 6}, 8},
    
    {{4, 7}, 9},
    {{4, 8}, 10},
    {{7, 8}, 11},

    {{5, 8}, 12},
    {{5, 9}, 13},
    {{8, 9}, 14},

    {{6, 9}, 15},
    {{6, 10}, 16},
    {{9, 10}, 17},
};
vector< tuple<int,int,int> > TRIANGLES = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {9, 10, 11},
    {12, 13, 14},
    {15, 16, 17},

    {2, 4, 6},
    {5, 10, 12},
    {8, 13, 15},
};
vector<vector<int>> edge_to_triangles(18);

void init() {
    REP(eid,18) {
        REP(tid,SZ(TRIANGLES)) {
            auto [x, y, z] = TRIANGLES[tid];
            if (eid == x || eid == y || eid == z) {
                edge_to_triangles[eid].push_back(tid);
            }
        }
    }
}

#define TWO(X) (1LL << (X))
bool contains(int s, int x) {
    return (s >> x) & 1;
}

// Given
// - `played` = set of edges already played,
// - `eid` = the next edge current player will play
// Returns how many triangles will be awarded to current player
int cnt_taken_triangle(int played, int eid) {
    assert(!contains(played, eid));
    played += TWO(eid);

    int res = 0;
    for (auto tid : edge_to_triangles[eid]) { // for each triangle containing `eid`
        auto [x, y, z] = TRIANGLES[tid];
        if (contains(played, x) && contains(played, y) && contains(played, z)) {
            ++res;
        }
    }
    return res;
}

vector<int> cached(TWO(18), 0), is_cached(TWO(18), false);
// Given:
// - `played` = set of edges already played
// Returns: maximum (triangles of current player) - (triangles of opponent)
//   assuming both player plays optimally
int f(int played) {
    if (is_cached[played]) return cached[played];
    if (played == TWO(18) - 1) return 0;

    int res = -1000;
    for (int eid = 0; eid < 18; ++eid) {
        if (!contains(played, eid)) {
            int c = cnt_taken_triangle(played, eid);
            if (c == 0) {
                res = max(res, -f(played + TWO(eid)));
            } else {
                res = max(res, c + f(played + TWO(eid)));
            }
        }
    }

    is_cached[played] = true;
    return cached[played] = res;
}

void solve() {
    init();

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int turn = 0;  // A
        int played = 0;
        int a_scores = 0;

        int n; cin >> n;
        while (n--) {
            int u, v; cin >> u >> v;

            int eid;
            auto p = make_pair(u, v);
            if (VERTICES_TO_EDGE_ID.count(p)) {
                eid = VERTICES_TO_EDGE_ID[p];
            } else {
                swap(p.first, p.second);
                assert(VERTICES_TO_EDGE_ID.count(p));
                eid = VERTICES_TO_EDGE_ID[p];
            }
            assert(!contains(played, eid));

            int c = cnt_taken_triangle(played, eid);
            played += TWO(eid);

            if (turn == 0) a_scores += c;
            else a_scores -= c;

            if (!c) turn = 1 - turn;
        }
        if (turn == 0) a_scores += f(played);
        else a_scores -= f(played);

        cout << "Game " << test << ": ";
        if (a_scores < 0) cout << "B wins.";
        else cout << "A wins.";
        cout << '\n';
    }
}
