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

const int MV = 1000111;
const int MN = 5011;
int f[MN][MN];
int cost[MN][MN];
short opt[MN][MN];
struct Point {
    int x, w;
};
bool operator < (const Point& a, const Point& b) {
    return a.x < b.x;
}
Point a[MN];

void solve() {
    vector<int> sumw(MV), sumwx(MV);

    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        int x, w; cin >> x >> w;
        sumw[x] += w;
        sumwx[x] += w * x;

        a[i] = Point {x, w};
    }
    sort(a+1, a+n+1);

    std::partial_sum(sumw.begin(), sumw.end(), sumw.begin());
    std::partial_sum(sumwx.begin(), sumwx.end(), sumwx.begin());

    if (k == n) {
        cout << 0 << endl;
        return;
    }

    // min cost for all people in range (l, r] to go left to l
    auto goLeft = [&] (int l, int r) {
        return sumwx[r] - sumwx[l] - (sumw[r] - sumw[l]) * l;
    };
    // min cost for all people in range (l, r] to go right to r
    auto goRight = [&] (int l, int r) {
        return (sumw[r] - sumw[l]) * r - (sumwx[r] - sumwx[l]);
    };
    // compute cost[i][j]
    FOR(i,1,n) FOR(j,i+1,n) {
        int mid = (a[i].x + a[j].x) / 2;
        cost[i][j] = goLeft(a[i].x, mid) + goRight(mid, a[j].x);
    }

    // f[i][j] = min cost to place i ships, last ship at j
    //           only consider people with x <= j
    memset(f, 0x7f, sizeof f);
    FOR(j,1,n) {
        f[1][j] = goRight(0, a[j].x);
        opt[1][j] = 1;
    }

    // compute f[i][j]
    FOR(i,2,k) {
        opt[i][n+1] = n;
        for (int j = n; j >= i; --j) {
            for (int last = opt[i-1][j]; last <= opt[i][j+1]; ++last) {
                int val = f[i-1][last] + cost[last][j];
                if (val < f[i][j]) {
                    f[i][j] = val;
                    opt[i][j] = last;
                }
            }
        }
    }

    int res = 1000111000111000111LL;
    FOR(last,1,n) {
        int cur = f[k][last] + goLeft(a[last].x, 1000001);
        res = min(res, cur);
    }
    cout << res << endl;
}
