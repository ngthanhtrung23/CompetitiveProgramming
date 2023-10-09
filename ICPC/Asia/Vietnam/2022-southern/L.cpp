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

const int MN = 1011;
int f[MN][2];

void upMax(int& f, int val) {
    f = max(f, val);
}

void solve() {
    int n;
    while (cin >> n) {
        if (!n) break;

        string a, b, c;
        cin >> a >> b >> c;
        a = " " + a + " ";
        b = " " + b + " ";
        c = " " + c + " ";

        memset(f, -1, sizeof f);
        f[n+1][0] = 0;
        for (int i = n+1; i >= 2; --i) {
            for (int rem = 0; rem < 2; ++rem) {
                int cur = f[i][rem];
                if (cur < 0) continue;  // invalid state

                // get next digits (at position i-1)
                int da = a[i-1] - '0';
                int db = b[i-1] - '0';
                int dc = c[i-1] - '0';

                // select column i-1
                int sum = da + db + rem;
                if (sum % 10 == dc) {
                    upMax(f[i-1][sum / 10], cur + 1);
                }

                // do not select column i-1
                upMax(f[i-1][rem], cur);
            }
        }
        cout << n - f[1][0] << '\n';
    }
}
