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

// NOTE: gP(n) is incorrect for even values of n
#define N 10000
unsigned mark[N / 64 + 1];
// DO NOT USE gP(n) directly.
#define gP(n) (mark[(n)>>6]&(1<<(((n)>>1)&31)))
#define rP(n) (mark[(n)>>6]&=~(1<<(((n)>>1)&31)))

// prime indexed from 0
int prime[5222222], nprime;

void sieve() {
    memset(mark, -1, sizeof mark);
    int i;
    int sqrtN = (int)sqrt((double) N) + 1;

    for (i = 3; i < sqrtN; i += 2) if (gP(i)) {
        int i2 = i + i;
        for (int j = i * i; j < N; j += i2) rP(j);
    }
    nprime = 0;
    prime[nprime++] = 2;
    for (i = 3; i < N; i += 2)
        if (gP(i)) prime[nprime++] = i;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    if (gP(n)) return true;
    return false;
}

int f[20][3][155][155];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    sieve();

    string s; cin >> s;
    int n = SZ(s);
    vector<int> digits(n);
    std::transform(s.begin(), s.end(), digits.begin(), [](char c) { return (int) (c - '0'); });

    f[n][0][0][0] = 1;
    // built digits i -> n
    for (int i = n; i > 0; i--) {
        REP(rem,3) REP(sumx,150) REP(sumy,150) {
            int cur = f[i][rem][sumx][sumy];
            if (!cur) continue;

            // loop through all possible digits
            REP(x,10) REP(y,10) {
                int t = x + 2*y + rem;
                if (t % 10 == digits[i-1]) {
                    f[i-1][t / 10][sumx+x][sumy+y] += cur;
                }
            }
        }
    }
    int res = 0;
    FOR(sumx,1,155) FOR(sumy,1,155)
        if (isPrime(sumx) && isPrime(sumy)) {
            res += f[0][0][sumx][sumy];
        }
    cout << res << endl;
    return 0;
}

