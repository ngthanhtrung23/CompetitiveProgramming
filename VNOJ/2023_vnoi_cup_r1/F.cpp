// template {{{
// CF pragma: https://codeforces.com/blog/entry/96344
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#ifndef UNSAFE_NO_DEFINE_INT_LONG_LONG
#define int long long
#endif
#define I(x) int x; cin >> x;
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if (i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
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
    for (auto& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

// }}}
// i128 helper functions {{{
using i128 = __int128_t;
i128 str2i128(std::string str) {
    i128 ret = 0;
    bool minus = false;
    for (auto c : str) {
        if (c == '-')
            minus = true;
        else
            ret = ret * 10 + c - '0';
    }
    return minus ? -ret : ret;
}
std::istream &operator>>(std::istream &is, i128 &x) {
    std::string s;
    return is >> s, x = str2i128(s), is;
}
std::ostream &operator<<(std::ostream &os, const i128 &x) {
    i128 tmp = x;
    if (tmp == 0) return os << 0;
    std::vector<int> ds;
    if (tmp < 0) {
        os << '-';
        while (tmp) {
            int d = tmp % 10;
            if (d > 0) d -= 10;
            ds.emplace_back(-d), tmp = (tmp - d) / 10;
        }
    } else {
        while (tmp) ds.emplace_back(tmp % 10), tmp /= 10;
    }
    std::reverse(ds.begin(), ds.end());
    for (auto i : ds) os << i;
    return os;
}
i128 my_abs(i128 n) {
    if (n < 0) return -n;
    return n;
}
i128 gcd(i128 a, i128 b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
// Count trailing zeroes
int ctz128(i128 n) {
    if (!n) return 128;
 
    if (!static_cast<uint64_t>(n)) {
        return __builtin_ctzll(static_cast<uint64_t>(n >> 64)) + 64;
    } else {
        return __builtin_ctzll(static_cast<uint64_t>(n));
    }
}
// }}}

void one();
void solve() {
    int ntest; cin >> ntest;
    while (ntest--) {
        one();
    }
}

struct Market {
    int can, cost;
};

struct Set : multiset<pair<int,int>> {
    int sum = 0;

    void add(const pair<int,int>& p) {
        insert(p);
        sum += p.second;
    }

    void rem(multiset<pair<int,int>>::iterator it) {
        sum -= it->second;
        erase(it);
    }
};

void one() {
    int nDays, cap, feed;
    cin >> nDays >> cap >> feed;
    vector<Market> buys(nDays), sells(nDays);
    REP(i,nDays) {
        cin >> buys[i].can >> buys[i].cost;
        cin >> sells[i].can >> sells[i].cost;
    }

    Set can_buys; // cost - i*feed, can

    auto ensure_limit = [&] () {
        while (can_buys.sum > cap) {
            int cur_sum = can_buys.sum;

            auto it = std::prev(can_buys.end());
            auto [p, cnt] = *it;
            can_buys.rem(it);

            int reduce = min(cnt, cur_sum - cap);
            cnt -= reduce;
            if (cnt > 0) {
                can_buys.add({p, cnt});
            }
        }
    };

    i128 res = 0;
    REP(i,nDays) {
        // try selling
        int sell_price = sells[i].cost - i * feed;
        int can_sell = sells[i].can;
        int buy_back = 0;
        while (!can_buys.empty() && can_buys.begin()->first < sell_price && can_sell > 0) {
            auto [buy_price, can_buy] = *can_buys.begin();
            can_buys.rem(can_buys.begin());

            int match = min(can_buy, can_sell);
            res += match * (sell_price - buy_price);
            can_buy -= match;
            can_sell -= match;
            if (can_buy > 0) {
                can_buys.add({buy_price, can_buy});
            }

            // allow buy back
            buy_back += match;
        }
        assert(buy_back == sells[i].can - can_sell);

        // allow buy back
        can_buys.add({sell_price, buy_back});
        // buy
        can_buys.add({buys[i].cost - i * feed, buys[i].can});

        ensure_limit();
    }
    cout << res << endl;
}
