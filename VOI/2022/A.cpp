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
long long get_rand(long long r) {  // [0, r)
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {  // [l, r]
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

void solve0(vector<pair<int,int>>& a) {
    // count: a[i] + a[j]
    unordered_map<int, int> res;
    for (int i = 0; i < SZ(a); ++i) {
        for (int j = i + 1; j < SZ(a); ++j) {
            res[a[i].first + a[j].first] += min(a[i].second, a[j].second);
        }
        res[a[i].first + a[i].first] += a[i].second / 2;
    }

    int ln = 0;
    for (auto [sum, cnt] : res) ln = max(ln, cnt);
    cout << ln << endl;
}

void solve() {
#ifndef RR
    freopen("PAIR.INP", "r", stdin);
    freopen("PAIR.OUT", "w", stdout);
#endif

    int n, d; cin >> n >> d;

    vector<int> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];
    sort(values.begin(), values.end());

    // (value, cnt)
    vector<pair<int,int>> a;
    for (int i = 0; i < n; ++i) {
        if (a.empty() || values[i] > a.back().first) {
            a.emplace_back(values[i], 1);
        } else {
            a.back().second += 1;
        }
    }

    if (d == 0) {
        solve0(a);
        return;
    }

    // find all possible values of a[i] + a[j]
    unordered_set<int> all;
    for (int i = 0; i < SZ(a); ++i) {
        for (int j = i; j < SZ(a); ++j) {
            all.insert(a[i].first + a[j].first);
        }
    }

    // for each possible sum x: a[i] + a[j] = x or x+1
    int res = 0;
    for (int sum : all) {
        unordered_map<int, int> cnt;
        for (int i = 0; i < SZ(a); ++i) {
            cnt[a[i].first] = a[i].second;
        }

        int cur = 0;
        for (int i = 0; i < SZ(a); ++i) {
            if (a[i].first * 2 == sum) {
                int can = min(cnt[a[i].first], cnt[a[i].first + 1]);
                cnt[a[i].first] -= can;
                cnt[a[i].first + 1] -= can;
                cur += can;

                cur += cnt[a[i].first] / 2;
                continue;
            }
            if (a[i].first * 2 == sum + 1) {
                cur += cnt[a[i].first] / 2;
                continue;
            }

            // sum + 1
            int aj1 = sum + 1 - a[i].first;
            int can = min(cnt[a[i].first], cnt[aj1]);
            cnt[aj1] -= can;
            cnt[a[i].first] -= can;
            cur += can;

            // sum
            int aj = sum - a[i].first;
            can = min(cnt[a[i].first], cnt[aj]);
            cnt[a[i].first] -= can;
            cnt[aj] -= can;
            cur += can;
        }

        res = max(res, cur);
    }
    cout << res << endl;
}

/*
 * x / x+1
 *
 * a[i] + a[j] = x
 *
 * (a[i]+1) + a[j] = x+1
 * a[i] + (a[j] + 1) = x+1
 */
