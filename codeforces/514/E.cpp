
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

// Assert with message
#define ASSERT(b, mess) { \
    if (!(b)) { \
        cout << mess << endl; \
        assert((b));\
    } \
}


const int MOD = 1e9 + 7;


template< class T >
struct Matrix {
    int m, n;
    vector< vector<T> > values;

    Matrix(int m, int n) : m(m), n(n), values(m, vector<T> (n)) {}

    vector<T>& operator [] (int i) {
        ASSERT(0 <= i && i < m, "Row index outside range [0,m)");
        return values[i];
    }

    Matrix<T> operator * (const Matrix<T>& a) {
        Matrix<T> res(m, a.n);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < a.n; ++j) {
                res.values[i][j] = 0;
                for(int k = 0; k < n; ++k)
                    res.values[i][j] = (res.values[i][j] + values[i][k] * a.values[k][j]) % MOD;
            }
        return res;
    }

    Matrix<T> operator % (long long k) {
        ASSERT(m == n, "Matrix opeartor ** : only square matrix allowed");
        Matrix res = identity(m);
        Matrix cur = (*this);
        while (k > 0) {
            if (k & 1) res = res * cur;
            cur = cur * cur;
            k >>= 1;
        }
        return res;
    }

    Matrix<T> identity(int n) {
        Matrix<T> res(n, n);
        for(int i = 0; i < n; ++i)
            res.values[i][i] = 1;
        return res;
    }
};


int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n, x;
    while (cin >> n >> x) {
        Matrix<long long> start(101, 1);
        Matrix<long long> transform(101, 101);
        REP(i,99) transform[i][i+1] = 1;
        transform[100][100] = 1;
        while (n--) {
            int u; cin >> u;
            transform[99][100-u] += 1;
            transform[100][100-u] += 1;
        }

        start[99][0] = 1;
        start[100][0] = 1;

        transform = transform % x;
        auto res = transform * start;
        cout << res[100][0] << endl;
    }
    return 0;
}
