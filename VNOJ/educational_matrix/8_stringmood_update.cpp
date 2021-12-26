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

// ModInt
inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
    unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
    asm(
        "divl %4; \n\t"
        : "=a" (d), "=d" (m)
        : "d" (xh), "a" (xl), "r" (y)
    );
#else
    __asm {
        mov edx, dword ptr[xh];
        mov eax, dword ptr[xl];
        div dword ptr[y];
        mov dword ptr[d], eax;
        mov dword ptr[m], edx;
    };
#endif
    out_d = d; out_m = m;
}

template<int MOD>
struct ModInt {
    unsigned x;

    constexpr ModInt() : x(0) { }
    constexpr ModInt(signed sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
    constexpr ModInt(signed long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }

#define COMPAREOP(OP) bool constexpr operator OP(ModInt b) const { return x OP b.x; }
    COMPAREOP(==) COMPAREOP(!=) COMPAREOP(<) COMPAREOP(>) COMPAREOP(<=) COMPAREOP(>=)
#undef COMPAREOP

    ModInt operator-() const { return ModInt(x ? MOD - x : 0); }

    ModInt constexpr& operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
    ModInt constexpr& operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator*=(ModInt that) {
        unsigned dummy;
        fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, x);
        return *this;
    }
    ModInt operator*(ModInt that) const {
        ModInt res;
        unsigned dummy;
        fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, res.x);
        return res;
    }
    ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
    ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }

    // Below: copied from user202729_, not tested.
    ModInt inv() const {
        int a = x, b = MOD, ax = 1, bx = 0;
        while (b) {
            int q = a/b, t = a%b;
            a = b; b = t;
            t = ax - bx*q;
            ax = bx; bx = t;
        }
        assert(a == 1);
        if (ax < 0) ax += MOD;
        return ax;
    }
    ModInt& operator /= (ModInt m) { return (*this) *= m.inv(); }
    ModInt operator / (ModInt that) const { return ModInt(*this) /= that; }
};
const int MOD = 1e9 + 7;
using modular = ModInt<MOD>;

std::ostream& operator << (std::ostream& cout, const modular& m) {
    cout << m.x;
    return cout;
}
std::istream& operator >> (std::istream& cin, modular& m) {
    cin >> m.x;
    return cin;
}

// Matrix
template<typename T>
struct Matrix {
    int n_row, n_col;
    vector<T> x;

    // accessors
    typename vector<T>::iterator operator [] (int r) {
        return x.begin() + r * n_col;
    }
    inline T get(int i, int j) const { return x[i * n_col + j]; }

    // constructors
    Matrix() = default;
    Matrix(int _n_row, int _n_col) : n_row(_n_row), n_col(_n_col), x(n_row * n_col) {}
    Matrix(const vector<vector<T>>& d) : n_row(d.size()), n_col(d.size() ? d[0].size() : 0) {
        for (auto& row : d) std::copy(row.begin(), row.end(), std::back_inserter(x));
    }

    // convert to 2d vec
    vector<vector<T>> vecvec() const {
        vector<vector<T>> ret(n_row);
        for (int i = 0; i < n_row; i++) {
            std::copy(x.begin() + i*n_col,
                    x.begin() + (i+1)*n_col,
                    std::back_inserter(ret[i]));
        }
        return ret;
    }
    operator vector<vector<T>>() const { return vecvec(); }

    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    Matrix transpose() const {
        Matrix res(n_col, n_row);
        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < n_col; j++) {
                res[j][i] = this->get(i, j);
            }
        }
        return res;
    }

    Matrix& operator *= (const Matrix& r) { return *this = *this * r; }
    Matrix operator * (const Matrix& r) const {
        assert(n_col == r.n_row);
        auto rt = r.transpose();
        Matrix res(n_row, r.n_col);

        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < rt.n_row; j++) {
                res[i][j] = std::inner_product(
                        this->x.begin() + n_col*i,
                        this->x.begin() + n_col*(i+1),
                        rt.x.begin() + rt.n_col*j,
                        T(0));
            }
        }
        return res;
    }

    Matrix pow(long long n) const {
        assert(n_row == n_col);
        Matrix res = identity(n_row);
        if (n == 0) return res;

        bool res_is_id = true;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
            if (!res_is_id) res *= res;
            if ((n >> i) & 1) res *= (*this), res_is_id = false;
        }
        return res;
    }

    // Gauss
    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept {
        int piv = -1;
        for (int j = h; j < mtr.n_row; j++) {
            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c)))) piv = j;
        }
        return piv;
    }
    template <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept {
        for (int j = h; j < mtr.n_row; j++) {
            if (mtr.get(j, c) != T(0)) return j;
        }
        return -1;
    }

    // return upper triangle matrix
    Matrix gauss() const {
        int c = 0;
        Matrix mtr(*this);
        vector<int> ws;
        ws.reserve(n_col);

        for (int h = 0; h < n_row; h++) {
            if (c == n_col) break;
            int piv = choose_pivot(mtr, h, c);
            if (piv == -1) {
                c++;
                h--;
                continue;
            }
            if (h != piv) {
                for (int w = 0; w < n_col; w++) {
                    swap(mtr[piv][w], mtr[h][w]);
                    mtr[piv][w] *= -1; // for determinant
                }
            }
            ws.clear();
            for (int w = c; w < n_col; w++) {
                if (mtr[h][w] != 0) ws.emplace_back(w);
            }
            const T hcinv = T(1) / mtr[h][c];
            for (int hh = 0; hh < n_row; hh++) {
                if (hh != h) {
                    const T coeff = mtr[hh][c] * hcinv;
                    for (auto w : ws) mtr[hh][w] -= mtr[h][w] * coeff;
                    mtr[hh][c] = 0;
                }
            }
            c++;
        }
        return mtr;
    }

    // For upper triangle matrix
    T det() const {
        T ret = 1;
        for (int i = 0; i < n_row; i++) {
            ret *= get(i, i);
        }
        return ret;
    }

    // return rank of inverse matrix. If rank < n -> not invertible
    int inverse() {
        assert(n_row == n_col);
        vector<vector<T>> ret = identity(n_row), tmp = *this;
        int rank = 0;

        for (int i = 0; i < n_row; i++) {
            int ti = i;
            while (ti < n_row && tmp[ti][i] == 0) ++ti;
            if (ti == n_row) continue;
            else ++rank;

            ret[i].swap(ret[ti]);
            tmp[i].swap(tmp[ti]);

            T inv = T(1) / tmp[i][i];
            for (int j = 0; j < n_col; j++) ret[i][j] *= inv;
            for (int j = i+1; j < n_col; j++) tmp[i][j] *= inv;

            for (int h = 0; h < n_row; h++) {
                if (i == h) continue;
                const T c = -tmp[h][i];
                for (int j = 0; j < n_col; j++) ret[h][j] += ret[i][j] * c;
                for (int j = i+1; j < n_col; j++) tmp[h][j] += tmp[i][j] * c;
            }
        }

        *this = ret;
        return rank;
    }
};

void print(const Matrix<modular>& a) {
    REP(i,a.n_row) {
        REP(j,a.n_col) {
            cout << a.get(i, j) << ' ';
        }
        cout << endl;
    }
}

// SegTree
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

template<
    class T,  // data type for nodes
    T (*op) (const T&, const T&),  // operator to combine 2 nodes
    T (*e)() // identity element
>
struct SegTree {
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<T> (n, e())) {}
    explicit SegTree(const vector<T>& v) : _n((int) v.size()) {
        log = ceil_pow2(_n);
        size = 1<<log;
        d = vector<T> (2*size, e());

        for (int i = 0; i < _n; i++) d[size+i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    // 0 <= p < n
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // 0 <= p < n
    T get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    // Get product in range [l, r-1]
    // 0 <= l <= r <= n
    // For empty segment (l == r) -> return e()
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        T sml = e(), smr = e();
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    T all_prod() const {
        return d[1];
    }

    // Binary search on SegTree to find largest r:
    //    f(op(a[l] .. a[r-1])) = true   (assuming empty array is always true)
    //    f(op(a[l] .. a[r])) = false    (assuming op(..., a[n]), which is out of bound, is always false)
    template <bool (*f)(T)> int max_right(int l) const {
        return max_right(l, [](T x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        T sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // Binary search on SegTree to find smallest l:
    //    f(op(a[l] .. a[r-1])) = true      (assuming empty array is always true)
    //    f(op(a[l-1] .. a[r-1])) = false   (assuming op(a[-1], ..), which is out of bound, is always false)
    template <bool (*f)(T)> int min_left(int r) const {
        return min_left(r, [](T x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        T sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    vector<T> d;

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }
};

// SegTree operations
Matrix<modular> op(const Matrix<modular>& l, const Matrix<modular>& r) {
    return l * r;
}
Matrix<modular> e() {
    return Matrix<modular>::identity(2);
}

Matrix<modular> get(char c) {
    if (c == '?') {
        return Matrix<modular> ({
            {19, 6},
            {7, 20},
        });
    }

    if (c == 'H') {
        return Matrix<modular> ({
            {1, 1},
            {0, 0},
        });
    }

    if (c == 'S' || c == 'D') {
        return Matrix<modular> ({
            {0, 0},
            {1, 1},
        });
    }

    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return Matrix<modular> ({
            {0, 1},
            {1, 0},
        });
    }

    return Matrix<modular> ({
        {1, 0},
        {0, 1},
    });
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<Matrix<modular>> nodes;
    for (char c : s) {
        nodes.push_back(get(c).transpose());
    }
    SegTree<Matrix<modular>, op, e> st(nodes);

    auto get_answer = [&st] () {
        auto m = st.all_prod();
        return m[0][0];
    };
    cout << get_answer() << '\n';

    while (q--) {
        int pos; cin >> pos;
        char c; cin >> c;

        st.set(pos - 1, get(c).transpose());
        cout << get_answer() << '\n';
    }
    return 0;
}

