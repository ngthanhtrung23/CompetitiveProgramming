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
    int ntest; cin >> ntest;
    while (ntest--) {
        string s; cin >> s;
        REP(i,SZ(s)) if (s[i] == 'X') s[i] = ' ';
        istringstream ss(s);

        vector<int> slots;
        string tmp;
        while (ss >> tmp) {
            int cur = SZ(tmp);
            if (cur < 2) {
            } else if (cur == 2) {
                slots.push_back(2);
            } else {
                slots.push_back(cur - 1);
            }
        }

        string types; cin >> types;
        // Normally we try to 'expand' cars & motorbikes, so
        //  M = 2 positions
        //  C = 3 positions
        // but for Tipu, he will try to occupy minimum amount of spaces
        types = "M" + types;

        // check whether we can fit first 'x' vehicles into the slots
        auto check = [types] (int x, vector<int> slots) -> bool {
            int n_car = 0, n_motor = 0;
            for (int i = 0; i <= x; i++) {
                if (types[i] == 'C') ++n_car;
                else ++n_motor;
            }

            for (int& slot : slots) {
                if (slot >= 3 && slot % 2 == 1 && n_car > 0) {
                    // we need to use either 1 car or 2 motor to clear
                    // last 3 positions in this slot
                    // --> using 1 car is always better
                    n_car--;
                    slot -= 3;
                }
            }

            multiset<int, std::greater<int>> st;
            for (int slot : slots) {
                if (slot >= 1) st.insert(slot);
            }

            // prioritize putting cars
            while (!st.empty()) {
                int cur = *st.begin();
                st.erase(st.begin());

                if (cur >= 6 && n_car >= 2) {
                    cur -= 6;
                    n_car -= 2;

                    if (cur >= 1) st.insert(cur);
                } else if (cur >= 1 && n_car >= 1) {
                    cur -= 3;
                    n_car -= 1;

                    if (cur >= 1) st.insert(cur);
                } else if (cur >= 1 && n_motor >= 1) {
                    cur -= 2;
                    n_motor -= 1;

                    if (cur >= 1) st.insert(cur);
                } else {
                    break;
                }
            }

            return n_car <= 0 && n_motor <= 0;
        };

        // binary search to find maximum number of vehicles we can fit
        // into the slots
        int l = 0, r = SZ(types) - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid, slots)) {
                res = mid;
                l = mid + 1;
            } else r = mid - 1;
        }

        FOR(i,0,SZ(types)-1) {
            cout << (res >= i ? 'Y' : 'N');
        }
        cout << '\n';
    }
    return 0;
}
