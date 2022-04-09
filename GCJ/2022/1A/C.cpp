#include "bits/stdc++.h"
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2,tune=native")
using namespace std;

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

using Req = vector<int>;
using State = vector<int>;

int E, W;
void gen(Req& req, State& cur, vector<State>& states) {
    if (accumulate(req.begin(), req.end(), 0) == 0) {
        states.push_back(cur);
    }

    REP(i,W) {
        if (req[i] > 0) {
            req[i]--;
            cur.push_back(i);

            gen(req, cur, states);

            cur.pop_back();
            req[i]++;
        }
    }
}

int cost(const State& a, const State& b) {
    int same = 0;
    while (same < SZ(a) && same < SZ(b) && a[same] == b[same]) ++same;

    return SZ(a) - same + SZ(b) - same;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> E >> W;

        vector<Req> reqs(E);
        for (auto& req : reqs) {
            req.resize(W);
            REP(i,W) cin >> req[i];
        }

        vector<vector<State>> states(E + 1);
        states[0].push_back({});

        vector<vector<int>> f(E + 1);
        f[0].push_back(0);

        REP(i,E) {
            State state;
            gen(reqs[i], state, states[i + 1]);

            f[i + 1].resize(SZ(states[i + 1]));
        }

        FOR(i,1,E) {
            REP(j,SZ(states[i])) {
                f[i][j] = 1000111000;
                REP(j2,SZ(states[i-1])) {
                    f[i][j] = min(f[i][j], f[i-1][j2] + cost(states[i-1][j2], states[i][j]));
                }
            }
        }

        int res = *min_element(f.back().begin(), f.back().end());
        res += accumulate(reqs.back().begin(), reqs.back().end(), 0);

        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
