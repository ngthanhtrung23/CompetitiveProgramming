// Statement: in comments in https://codeforces.com/blog/entry/98670
// Idea: 
// - sum_xor(1..n) depends only on n % 4
// - case work for each n % 4

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

int sum_xor(int n) {
    if (n % 4 == 3) return 0;
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return 1 ^ n;
}

int brute(int n) {
    int m;

    //
    m = n;
    if (sum_xor(m) == 0) return m;

    // 
    m = n + 1;
    int s = sum_xor(m);
    if (1 <= s && s <= m) {
        return m;
    }

    //
    m = n + 2;
    s = sum_xor(m);
    FOR(x,1,m) {
        int y = s ^ x;
        if (y != x && 1 <= y && y <= m) {
            return m;
        }
    }

    //
    m = n + 3;
    s = sum_xor(m);
    FOR(x,1,m) FOR(y,x+1,m) {
        int z = s ^ x ^ y;
        if (z != x && z != y && z <= m) {
            return m;
        }
    }

    return n + 4;
}

int n;
void print(int m, const vector<int>& rem) {
    int s = sum_xor(m);
    for (int r : rem) {
        s ^= r;
        assert(r <= m);
    }
    set<int> all(rem.begin(), rem.end());
    assert(SZ(all) == SZ(rem));
    assert(s == 0);

    cout << m << endl;
    for (int x : rem) cout << x << ' ';
    cout << endl;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        if (n % 4 == 3) {
            print(n, {});
        } else if (n % 4 == 0) {
            print(n+1, {1});
        } else if (n % 4 == 1) {
            int t = n / 4;
            if (t % 2) {
                {
                    int s = sum_xor(n + 3);
                    bool found = false;
                    for (int y = 8; y <= n+3; y *= 2) {
                        int x = 1;
                        int z = 1^y^s;
                        if (1 <= z && z <= n+3 && z != x && z != y) {
                            print(n+3, {x, y, z});
                            found = true;
                            break;
                        }
                    }
                    if (found) continue;
                }

                // n = 5, 13, 21..
                int m = n + 4;
                int s = sum_xor(m);

                print(m, {1, 2, (1^2^s^(m-2)), m-2});
            } else { // n = 9, 17..
                int m = n + 3;
                int s = sum_xor(m);
                print(m, {1, 1^s^(m-1), m-1});
            }
        } else {
            assert(n % 4 == 2);
            int t = n / 4;
            if (t % 2) {
                // n = 6, 14..
                {
                    int s = sum_xor(n + 2);
                    bool found = false;
                    for (int x = 8; x <= n+2; x *= 2) {
                        int y = x^s;
                        if (1 <= y && y <= n+2 && y != x) {
                            print(n+2, {x, y});
                            found = true;
                            break;
                        }
                    }
                    if (found) continue;
                }
                int m = n + 3;
                int s = sum_xor(m);
                print(m, {3, (s^3^(m-2)), m-2});
            } else {
                // n = 10, 18..
                int m = n + 2;
                int s = sum_xor(m);
                print(m, {s^(m-1), m-1});
            }
        }
    }
    return 0;
}
