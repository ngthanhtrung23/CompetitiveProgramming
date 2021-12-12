#include "bits/stdc++.h"
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
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

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

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

template<typename T>
struct Matrix {
    vector< vector<T> > x;

    Matrix() {
        x.clear();
    }
    Matrix(int m, int n) {
        x.resize(m);
        REP(i,m) {
            x[i].resize(n);
            REP(j,n) x[i][j] = 0;
        }
    }

    const vector<T>& operator [] (size_t i) const {
        return x[i];
    }
    
    vector<T>& operator [] (size_t i) {
        return x[i];
    }

    void print() {
        REP(i,SZ(x)) {
            REP(j,SZ(x[i])) cout << x[i][j] << ' ';
            cout << endl;
        }
    }

    Matrix transpose() const {
        int nRow = SZ(x);
        int nCol = SZ(x[0]);

        Matrix res(nCol, nRow);
        REP(i,nCol) REP(j,nRow) {
            res.x[i][j] = x[j][i];
        }
        return res;
    }
};

template<typename T>
Matrix<T> operator * (const Matrix<T> &a, const Matrix<T> &b) {
    if (SZ(a.x) == 0 || SZ(b.x) == 0) return Matrix<T>(); // not sure if make sense?

    Matrix<T> c(SZ(a.x), SZ(b[0]));
    REP(i,SZ(c.x)) REP(j,SZ(c[0])) {
        REP(k,SZ(a[0]))
            c[i][j] += a[i][k] * b[k][j];
    }
    return c;
}

template<typename T>
Matrix<T> identity(int n) {
    Matrix<T> res(n, n);
    REP(i,n) res.x[i][i] = 1;
    return res;
}

template<typename T>
Matrix<T> power(Matrix<T> a, int k) {
    assert(SZ(a.x) == SZ(a.x[0]));

    Matrix<T> res = identity<T>(a.x.size());

    while (k > 0) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }

    return res;
}

// https://en.wikipedia.org/wiki/Gaussian_elimination#Finding_the_inverse_of_a_matrix
// Only works if matrix is invertible
template<typename T>
Matrix<T> inverse(Matrix<T> a) {
    assert(SZ(a.x) == SZ(a[0]));
    int n = SZ(a.x);

    REP(i,n) {
        vector<T> tmp(n);
        tmp[i] = 1;
        a[i].insert(a[i].end(), tmp.begin(), tmp.end());
    }

    a.gauss();

    Matrix<T> inv(n, n);
    REP(i,n) REP(j,n) {
        inv[i][j] = a[i][j+n];
    }
    return inv;
}

string board[111];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int nRow, nCol, time; cin >> nRow >> nCol >> time;

    auto id = [&] (int r, int c) {
        if (r < 0 || r >= nRow) return -1LL;
        if (c < 0 || c >= nCol) return -1LL;
        if (board[r][c] == '#') return -1LL;
        return r * nCol + c;
    };
    REP(i,nRow) cin >> board[i];

    int n = nRow * nCol;
    Matrix<modular> transition(n, n);

    REP(r,nRow) REP(c,nCol) {
        int from = id(r, c);

        char cur = board[r][c];
        if (cur == 'L' || cur == '+') {
            int to = id(r, c - 1);
            if (to >= 0) transition[to][from] += 1;
        }
        if (cur == 'R' || cur == '+') {
            int to = id(r, c + 1);
            if (to >= 0) transition[to][from] += 1;
        }
        if (cur == 'U' || cur == '+') {
            int to = id(r - 1, c);
            if (to >= 0) transition[to][from] += 1;
        }
        if (cur == 'D' || cur == '+') {
            int to = id(r + 1, c);
            if (to >= 0) transition[to][from] += 1;
        }
    }

    Matrix res = power(transition, time);

    modular sum(0);
    for (auto row : res.x) {
        for (auto val : row) {
            sum += val;
        }
    }
    cout << sum << endl;

    return 0;
}
