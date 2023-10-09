// template {{{
#include <bits/stdc++.h>
using namespace std;

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
// Suffix Array {{{
// Source: http://codeforces.com/contest/452/submission/7269543
// Efficient Suffix Array O(N*logN)

// String index from 0
// Usage:
// string s;  (s[i] > 0)
// SuffixArray sa(s);
// Now we can use sa.SA and sa.LCP
// sa.LCP[i] = max common prefix suffix of sa.SA[i-1] and sa.SA[i]
//
// Notes:
// - Number of distinct substrings = |S| * (|S| + 1) / 2 - sum(LCP)
//
// Tested:
// - (build SA) https://judge.yosupo.jp/problem/suffixarray
// - (LCP) https://judge.yosupo.jp/problem/number_of_substrings
// - (LCP - kth distinct substr) https://cses.fi/problemset/task/2108
// - (LCP - longest repeated substr) https://cses.fi/problemset/task/2106/
struct SuffixArray {
    string a;
    int N, m;
    vector<int> SA, LCP, x, y, w, c;

    SuffixArray(string _a, int _m = 256) : a(" " + _a), N(a.length()), m(_m),
            SA(N), LCP(N), x(N), y(N), w(max(m, N)), c(N) {
        a[0] = 0;
        DA();
        kasaiLCP();
        #define REF(X) { rotate(X.begin(), X.begin()+1, X.end()); X.pop_back(); }
        REF(SA); REF(LCP);
        a = a.substr(1, a.size());
        for(int i = 0; i < (int) SA.size(); ++i) --SA[i];
        #undef REF
    }

    inline bool cmp (const int u, const int v, const int l) {
        return (y[u] == y[v] && (u + l < N && v + l < N ? y[u + l] == y[v + l] : false));
    }

    void Sort() {
        for(int i = 0; i < m; ++i) w[i] = 0;
        for(int i = 0; i < N; ++i) ++w[x[y[i]]];
        for(int i = 0; i < m - 1; ++i) w[i + 1] += w[i];
        for(int i = N - 1; i >= 0; --i) SA[--w[x[y[i]]]] = y[i];
    }

    void DA() {
        for(int i = 0; i < N; ++i) x[i] = a[i], y[i] = i;
        Sort();
        for(int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
            for(p = 0, i = N - j; i < N; i++) y[p++] = i;
            for (int k = 0; k < N; ++k) if (SA[k] >= j) y[p++] = SA[k] - j;
            Sort();
            for(swap(x, y), p = 1, x[SA[0]] = 0, i = 1; i < N; ++i)
                x[SA[i]] = cmp(SA[i - 1], SA[i], j) ? p - 1 : p++;
        }
    }

    void kasaiLCP() {
        for (int i = 0; i < N; i++) c[SA[i]] = i;
        for (int i = 0, j, k = 0; i < N; LCP[c[i++]] = k)
            if (c[i] > 0) for (k ? k-- : 0, j = SA[c[i] - 1]; a[i + k] == a[j + k]; k++);
            else k = 0;
    }
};

// Example:
// given string S and Q queries pat_i, for each query, count how many
// times pat_i appears in S
// O(min(|S|, |pat|) * log(|S|)) per query
//
// Tested:
// - (yes / no) https://cses.fi/problemset/task/2102
// - (count) https://cses.fi/problemset/task/2103
// - (position; need RMQ) https://cses.fi/problemset/task/2104
int count_occurrence(const string& s, const vector<int>& sa, const string& pat) {
    int n = s.size(), m = pat.size();
    assert(n == (int) sa.size());
    if (n < m) return 0;
 
    auto f = [&] (int start) {  // compare S[start..] and pat[0..]
        for (int i = 0; start + i < n && i < m; ++i) {
            if (s[start + i] < pat[i]) return true;
            if (s[start + i] > pat[i]) return false;
        }
        return n - start < m;
    };
    auto g = [&] (int start) {
        for (int i = 0; start + i < n && i < m; ++i) {
            if (s[start + i] > pat[i]) return false;
        }
        return true;
    };
    auto l = std::partition_point(sa.begin(), sa.end(), f);
    auto r = std::partition_point(l, sa.end(), g);
    return std::distance(l, r);
}
// }}}
// RMQ {{{
//
// Sparse table
// Usage:
// RMQ<int, _min> st(v);
//
// Note:
// - doesn't work for empty range
//
// Tested:
// - https://judge.yosupo.jp/problem/staticrmq
template<class T, T (*op) (T, T)> struct RMQ {
    RMQ() = default;
    RMQ(const vector<T>& v) : t{v}, n{(int) v.size()} {
        for (int k = 1; (1<<k) <= n; ++k) {
            t.emplace_back(n - (1<<k) + 1);
            for (int i = 0; i + (1<<k) <= n; ++i) {
                t[k][i] = op(t[k-1][i], t[k-1][i + (1<<(k-1))]);
            }
        }
    }

    // get range [l, r]
    // doesn't work for empty range
    T get(int l, int r) const {
        ++r;
        assert(0 <= l && l < r && r <= n);

        int k = __lg(r - l);
        return op(t[k][l], t[k][r - (1<<k)]);
    }

private:
    vector<vector<T>> t;
    int n;
};
template<class T> T _min(T a, T b) { return b < a ? b : a; }
template<class T> T _max(T a, T b) { return a < b ? b : a; }
// }}}
// WaveletMatrix {{{
// Copied from https://github.com/dacin21/dacin21_codebook/blob/master/trees/wavelet_matrix.cpp
//
// Notes:
// - Index from 0
// - k (for k-th query) from 0
// - Need to remove #define int long long
//
// Tested:
// - (kth query) https://judge.yosupo.jp/problem/range_kth_smallest
// - (range_count) https://judge.yosupo.jp/problem/static_range_frequency

// Bit Presum {{{
class Bit_Presum {
public:
    static constexpr uint32_t omega = CHAR_BIT * sizeof(uint64_t);
    static constexpr uint32_t lg_omega = __lg(omega);
    static_assert(omega == 64u);

    Bit_Presum(vector<uint64_t> mask_)
            : n(mask_.size()), mask(move(mask_)), presum(n+1) {
        build();
    }
    Bit_Presum(uint32_t bits, bool init_val = 0)
            : n((bits>>lg_omega) + 1),
              mask(n, init_val ? ~uint64_t{0} : uint64_t{0}),
              presum(n+1) {
        if (init_val) mask.back()<<=((n<<lg_omega) - bits);
        build();
    }
    // popcount l <= i < r
    uint32_t query(uint32_t l, uint32_t r) const {
        if (__builtin_expect(r < l, false)) return 0;
        return query(r) - query(l);
    }
    // popcount 0 <= i < x
    uint32_t query(uint32_t x) const {
        uint32_t high = x>>lg_omega, low = x & ((uint64_t{1}<<lg_omega) - 1);
        uint32_t ret = presum_query(high);
        ret += __builtin_popcountll(mask[high]& ((uint64_t{1} << low)-1));
        return ret;
    }

    void update_pre_build(uint32_t x, bool val) {
        uint32_t high = x>>lg_omega, low = x & ((1u<<lg_omega) - 1);
        mask[high] = (mask[high] & ~(uint64_t{1} << low)) | (uint64_t{val}<<low);
    }
    void do_build() {
        build();
    }

    friend ostream& operator<<(ostream&o, Bit_Presum const&b) {
        for (auto const& e : b.mask) {
            stringstream ss;
            ss << bitset<omega>(e);
            auto s = ss.str();
            reverse(s.begin(), s.end());
            o << s << "|";
        }
        o << " : ";
        for (auto const&e:b.presum) o << e << " ";
        o << "\n";
        return o;
    }

private:
    void presum_build() {
        for (uint32_t x = 1; x <= n; ++x) {
            presum[x] += presum[x-1];
        }
    }
    // sum 0 <= i < x
    uint32_t presum_query(uint32_t x) const {
        return presum[x];
    }
    void build() {
        for (uint32_t x = 0; x < n; ++x) {
            presum[x+1] = __builtin_popcountll(mask[x]);
        }
        presum_build();
    }

    const uint32_t n;
    vector<uint64_t> mask;
    vector<uint32_t> presum;
};
// }}}

template<typename T, typename Bit_Ds = Bit_Presum>
class WaveletMatrix {
public:
    static_assert(is_integral<T>::value);
    static constexpr uint32_t height = CHAR_BIT * sizeof(T);

    WaveletMatrix(vector<T> v): n(v.size()), data(height, n) {
        build(move(v));
    }
    // count l <= i < r  s.t.  A <= val[i] < B
    uint32_t range_count(int l, int r, T A, T B) const {
        assert(0 <= l && r <= n);
        return count_lower(l, r, B) - count_lower(l, r, A);
    }
    // count l <= i < r  s.t.  A <= val[i]
    uint32_t range_count_up(int l, int r, T A) const {
        assert(0 <= l && r <= n);
        if (__builtin_expect(l>r, false)) return uint32_t{0};
        return (r-l) - count_lower(l, r, A);
    }
    // k from 0
    // range: [l, r-1]
    T k_th(int l, int r, int k) const {
        assert(0 <= k && k < n);
        return get_kth(l, r, k);
    }

    // internal functions {{{
private:
    void build(vector<T> v) {
        m_index.resize(height);
        T const a = numeric_limits<T>::min();
        for (int h = height-1; h>=0;--h) {
            T const b = a + (T{1}<<(max(0, h-1))) - !h + (T{1}<<(max(0, h-1)));
            for (int i=0;i<n;++i) {
                data[h].update_pre_build(i, v[i]<b);
            }
            data[h].do_build();
            const int m = stable_partition(v.begin(), v.end(), [&b](T const&x) {return x < b;}) - v.begin();
            for (int i=m;i<n;++i) {
                v[i] = v[i] - (T{1}<<(max(0, h-1))) + !h - (T{1}<<(max(0, h-1)));
            }
            m_index[h] = m;
        }
    }
    /// count l <= i < r  s.t.  val[i] < B
    uint32_t count_lower(int l, int r, T const&B) const {
        assert(0 <= l && r <= n);
        if (__builtin_expect(r<l, false)) return 0;
        uint32_t ret = 0;
        int h = height;
        T a = numeric_limits<T>::min();
        while(h > 0) {
            --h;
			bool go_left = B < a + (T{1}<<(max(0, h-1))) - !h + (T{1}<<(max(0, h-1)));
            const int low_l = data[h].query(l), low_r = data[h].query(r);
            if (go_left) {
                l = low_l;
                r = low_r;
            } else {
                a = a + (T{1}<<(max(0, h-1))) - !h + (T{1}<<(max(0, h-1)));
                ret+= low_r-low_l;
                l = m_index[h] + l-low_l;
                r = m_index[h] + r-low_r;
            }
        }
        return ret;
    }
    T get_kth(int l, int r, int k) const {
        assert(0 <= l && r <= n);
        assert(0 <= k && k < r-l);
        int h = height;
        T a = numeric_limits<T>::min();
        while (h > 0) {
            --h;
            const int low_l = data[h].query(l), low_r = data[h].query(r), low_lr = low_r-low_l;
            bool go_left = k < low_lr;
            if (go_left) {
                l = low_l;
                r = low_r;
            } else {
                a+= T{1}<<h;
                k-= low_lr;
                l = m_index[h] + l-low_l;
                r = m_index[h] + r-low_r;
            }
        }
        return a;
    }

    const int n;
    vector<int> m_index;
    vector<Bit_Ds> data;
    // }}}
};
// }}}

void solve() {
    string s, t;
    cin >> s >> t;
    char c = 127;
    string combined = s + c + t;

    SuffixArray sa(combined);

    vector<int> s_id_of(s.size());
    for (int i = 0; i < SZ(sa.SA); ++i) {
        if (sa.SA[i] < SZ(s)) {
            s_id_of[sa.SA[i]] = i;
        }
    }

    RMQ<int, _min> rmq(sa.LCP);
    auto getLeft = [&] (int u, int need) {
        int l = 0, r = u - 1, res = u;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (rmq.get(mid+1, u) >= need) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res;
    };
    auto getRight = [&] (int u, int need) {
        int l = u + 1, r = SZ(combined) - 1, res = u;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (rmq.get(u+1, mid) >= need) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    };

    WaveletMatrix<int> wm(sa.SA);

    int q; cin >> q;
    while (q--) {
        int sleft, sright, tleft, tright;
        cin >> sleft >> sright >> tleft >> tright;
        --sleft; --sright;
        --tleft; --tright;

        if (sleft > sright || tleft > tright) {
            cout << 0 << '\n';
            continue;
        }

        if (sleft < 0 || sright >= SZ(s) || tleft < 0 || tright >= SZ(t)) {
            cout << 0 << '\n';
            continue;
        }
        assert(0 <= sleft && sleft <= sright && sright < SZ(s));
        assert(0 <= tleft && tleft <= tright && tright < SZ(t));

        int slen = sright - sleft + 1;

        int l = getLeft(s_id_of[sleft], slen);
        int r = getRight(s_id_of[sleft], slen);

        int A = tleft + SZ(s) + 1;
        int B = (tright - slen + 1) + (SZ(s) + 1);

        int res = 0;
        if (A <= B) {
            res = wm.range_count(l, r+1, A, B+1);
        }
        
        cout << res << '\n';
    }
}
