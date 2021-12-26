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

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    double p; cin >> p;
    // f[i] = f[i-1] * (1-p) + g[i-1] * p
    // g[i] = f[i-1] * p + g[i-1] * (1-p)
    //
    // [....]  [f(i-1)]
    // [....]  [g(i-1)]
    Matrix<double> trans({
        {1-p, p},
        {p, 1-p},
    });
    cout << (fixed) << setprecision(9) << trans.pow(n)[0][0] << endl;
    return 0;
}
