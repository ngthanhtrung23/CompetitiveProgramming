#include <bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
using namespace std;

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

template<int MOD>
ModInt<MOD> power(ModInt<MOD> n, long long k) {
    if (k == 0) return ModInt<MOD> (1);
    ModInt<MOD> res(1);
    while (k > 0) {
        if (k & 1) res = res * n;
        n = n * n;
        k >>= 1;
    }
    return res;
}

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
        Matrix res(n_row, r.n_col);

        for (int i = 0; i < n_row; i++) {
            for (int k = 0; k < n_col; k++) {
                for (int j = 0; j < r.n_col; j++) {
                    res[i][j] += this->get(i, k) * r.get(k, j);
                }
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

int contains(int mask, int bit) {
    return (mask >> bit) & 1;
}
int two(int x) {
    return 1<<x;
}

int apply_vertical(int mask, int r, int vertical) {
    for (int row = 0; row < r-1; row++) {
        if (contains(vertical, row)) {
            assert(!contains(vertical, row + 1));
            mask += two(row);
            mask += two(row + 1);
        }
    }
    return mask;
}

bool can_apply_vertical(int mask, int r, int vertical) {
    if ((vertical & (vertical >> 1)) != 0) return false;
    for (int row = 0; row < r-1; row++) if (contains(vertical, row)) {
        if (contains(mask, row)) return false;
        if (contains(mask, row + 1)) return false;
    }
    return true;
}

int main() {
#define int long long
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int r, n, k; std::cin >> r >> n >> k;
    std::map<int, int> blockColumns;
    while (k--) {
        int x, y; std::cin >> x >> y;
        blockColumns[y] |= two(x - 1);
    }
    if (!blockColumns.count(n)) blockColumns[n] = 0;

    // f[i][mask] = finished tiling first i columns
    //              mask represent which rows is tiled
    
    Matrix<modular> trans(two(r), two(r));
    for (int cur = 0; cur < two(r); cur++) {
        int fill_horizontal = two(r) - 1 - cur;
        int next = fill_horizontal;

        for (int next_vertical = 0; next_vertical < two(r-1); next_vertical++) {
            if (can_apply_vertical(next, r, next_vertical)) {
                int next_mask = apply_vertical(next, r, next_vertical);
                assert(0 <= next_mask && next_mask < two(r));
                trans[next_mask][cur] += 1;
            }
        }
    }

    Matrix<modular> cur(two(r), 1);
    cur[two(r) - 1][0] = 1;
    int cur_i = 0;

    for (auto [col, blocked_mask] : blockColumns) {
        cur = trans.pow(col - cur_i) * cur;

        Matrix<modular> next(two(r), 1);
        for (int mask = 0; mask < two(r); mask++) {
            if ((mask & blocked_mask) == 0) {
                assert((mask | blocked_mask) < two(r));
                next[mask | blocked_mask][0] = cur[mask][0];
            }
        }

        cur_i = col;
        cur = next;
    }
    cout << cur[two(r) - 1][0] << endl;
    return 0;
}
