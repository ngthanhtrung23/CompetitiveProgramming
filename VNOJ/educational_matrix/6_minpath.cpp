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

const int INF = 2e18;

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
        REP(i,n) REP(j,n) {
            res[i][j] = INF;
        }
        return res;
    }

    Matrix& operator *= (const Matrix& r) { return *this = *this * r; }
    Matrix operator * (const Matrix& r) const {
        assert(n_col == r.n_row);
        Matrix res(n_row, r.n_col);

        for (int i = 0; i < res.n_row; i++) {
            for (int j = 0; j < res.n_col; j++) {
                res[i][j] = INF;
                for (int k = 0; k < n_col; k++) {
                    int u = this->get(i, k);
                    int v = r.get(k, j);
                    
                    if (u < INF && v < INF) {
                        res[i][j] = min(res[i][j], u + v);
                    }
                }
            }
        }
        return res;
    }
};

void print(const Matrix<int>& a) {
    REP(i,a.n_row) {
        REP(j,a.n_col) {
            if (a.get(i, j) == INF) cout << '-';
            else cout << a.get(i, j);
            cout << ' ';
        }
        cout << endl;
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;

    Matrix<int> trans = Matrix<int>::identity(n);

    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        --u; --v;
        trans[u][v] = c;
    }

    Matrix res = Matrix<int>::identity(n);
    REP(i,n) res[i][i] = 0;
    while (k > 0) {
        if (k & 1) {
            res = res * trans;
        }
        k >>= 1;
        trans = trans * trans;
    }

    int nn = INF;
    REP(i,n) REP(j,n) {
        nn = min(nn, res[i][j]);
    }
    if (nn == INF) cout << "IMPOSSIBLE" << endl;
    else cout << nn << endl;
    return 0;
}

