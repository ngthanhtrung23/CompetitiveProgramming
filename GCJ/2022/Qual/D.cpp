#include "bits/stdc++.h"
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2,tune=native")
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
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

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

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int r) {
    return uniform_int_distribution<int> (0, r-1)(rng);
}

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; std::cin >> ntest;

    FOR(test,1,ntest) {
        int n; std::cin >> n;
        std::vector<int> f(n); for (int& x : f) std::cin >> x;
        std::vector<int> to(n);
        const int INF = 1000111000;
        std::vector<int> min_prev(n, INF);

        std::vector<int> in_deg(n);
        REP(i,n) {
            std::cin >> to[i];
            to[i]--;

            if (to[i] < 0) continue;
            in_deg[to[i]]++;
        }

        std::stack<int> st;
        REP(i,n) {
            if (in_deg[i] == 0) {
                st.push(i);
                min_prev[i] = 0;
            }
        }

        int res = 0;
        std::vector<bool> visited(n, false);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            visited[u] = true;

            if (f[u] > min_prev[u]) {
                res += f[u] - min_prev[u];
            }

            int v = to[u];
            if (v < 0) continue;
            min_prev[v] = std::min(min_prev[v], std::max(f[u], min_prev[u]));
            --in_deg[v];
            if (!in_deg[v]) st.push(v);
        }

        REP(i,n) {
            if (!visited[i]) {
                int start = i;
                int u = i;
                int sum = 0;
                int min_prevs = INF;
                do {
                    visited[u] = true;
                    sum += f[u];
                    min_prevs = std::min(min_prevs, min_prev[u]);
                    int v = to[u];
                    u = v;
                } while (u != start);

                if (min_prevs == INF) min_prevs = 0;

                res += sum - min_prevs;
            }
        }

        std::cout << "Case #" << test << ": ";
        std::cout << res << std::endl;
    }
    return 0;
}

