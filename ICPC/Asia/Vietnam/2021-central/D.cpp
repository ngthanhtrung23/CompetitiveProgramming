// A = [
//   [1 2 3 4 5]
//   [6 7 8 9 10]
//   [11 12 13 14 15]
//   [16 17 18 19 20]
//   [21 22 23 24 25]
// ]
//
// B = [
//   [10 20 30]
//   [40 50 60]
//   [70 80 90]
// ]
//
// Calculate convolution:
//   res(i, j) = sum(B(x, y) * A(i + (x-1)/2, j + (y-1)/2))
//
//   e.g.
//   res(0, 0) = 1*50 + 2*60 + 6*80 + 7*90
//   res(1, 1) = 1*10 + 2*20 + 3*30 + 6*40 + 7*50 + 8*60 + 11*70 + 12*80 + 13*90
//
// Sol:
// - flatten A and B
//   [1 2 3 4 5     0 0 0 0 0   6 7 8 9 10    0 0 0 0 0  11 12 13 14 15 ...]
//   [90 80 70 0 0  0 0 0 0 0   60 50 40 0 0  0 0 0 0 0  30 20 10 0 0   ...]
//
// - Multiply A*B
//   res(i, j) = A*B(i + (x-1)/2, j + (y-1)/2)

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

// Copied from chemthan
template<const int mod, const int maxf>
struct NTT {
    NTT() {
        int k = 0; while ((1 << k) < maxf) k++;
        bitrev[0] = 0;
        for (int i = 1; i < maxf; i++) {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (k - 1));
        }
        int pw = fpow(prt(), (mod - 1) / maxf);
        rts[0] = 1;
        for (int i = 1; i <= maxf; i++) {
            rts[i] = (long long) rts[i - 1] * pw % mod;
        }
        for (int i = 1; i <= maxf; i <<= 1) {
            iv[i] = fpow(i, mod - 2);
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b) {
        static int fa[maxf], fb[maxf], fc[maxf];
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        multiply(fa, fb, na, nb, fc);
        int k = na + nb - 1;
        vector<int> res(k);
        for (int i = 0; i < k; i++) res[i] = fc[i];
        return res;
    }

private:
    int rts[maxf + 1];
    int bitrev[maxf];
    int iv[maxf + 1];

    int fpow(int a, int k) {
        if (!k) return 1;
        int res = a, tmp = a;
        k--;
        while (k) {
            if (k & 1) {
                res = (long long) res * tmp % mod;
            }
            tmp = (long long) tmp * tmp % mod;
            k >>= 1;
        }
        return res;
    }
    int prt() {
        vector<int> dvs;
        for (int i = 2; i * i < mod; i++) {
            if ((mod - 1) % i) continue;
            dvs.push_back(i);
            if (i * i != mod - 1) dvs.push_back((mod - 1) / i);
        }
        for (int i = 2; i < mod; i++) {
            int flag = 1;
            for (int j = 0; j < (int) dvs.size(); j++) {
                if (fpow(i, dvs[j]) == 1) {
                    flag = 0;
                    break;
                }
            }
            if (flag) return i;
        }
        assert(0);
        return -1;
    }
    void dft(int a[], int n, int sign) {
        int d = 0; while ((1 << d) * n != maxf) d++;
        for (int i = 0; i < n; i++) {
            if (i < (bitrev[i] >> d)) {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int len = 2; len <= n; len <<= 1) {
            int delta = maxf / len * sign;
            for (int i = 0; i < n; i += len) {
                int *w = sign > 0 ? rts : rts + maxf;
                for (int k = 0; k + k < len; k++) {
                    int &a1 = a[i + k + (len >> 1)], &a2 = a[i + k];
                    int t = (long long) *w * a1 % mod;
                    a1 = a2 - t;
                    a2 = a2 + t;
                    a1 += a1 < 0 ? mod : 0;
                    a2 -= a2 >= mod ? mod : 0;
                    w += delta;
                }
            }
        }
        if (sign < 0) {
            int in = iv[n];
            for (int i = 0; i < n; i++) {
                a[i] = (long long) a[i] * in % mod;
            }
        }
    }
    void multiply(int a[], int b[], int na, int nb, int c[]) {
        static int fa[maxf], fb[maxf];
        int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = 0;
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        dft(fa, n, 1), dft(fb, n, 1);
        for (int i = 0; i < n; i++) fa[i] = (long long) fa[i] * fb[i] % mod;
        dft(fa, n, -1);
        for (int i = 0; i < n; i++) c[i] = fa[i];
    }
};

// Copied from chemthan
template<typename T>
struct CRT {
    T res;

    CRT() {
        res = 0, prd = 1;
    }
    
    // Add condition: res % p == r
    void add(T p, T r) {
        res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
        prd *= p;
        if (res >= prd) res -= prd;
    }

private:
    T prd;
    T mul(T a, T b, T p) {
        a %= p, b %= p;
        T q = (T) ((long double) a * b / p);
        T r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
    }
    pair<T, T> euclid(T a, T b) {
        if (!b) return make_pair(1, 0);
        pair<T, T> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
};

const int MOD0 = 1004535809; //2^21 * 479 + 1
const int MOD1 = 1012924417; //2^21 * 483 + 1
NTT<MOD0, 1 << 21> ntt0;
NTT<MOD1, 1 << 21> ntt1;

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int h, w, x, y;
    while (cin >> h >> w >> x >> y) {
        vector<vector<int>> a(h, vector<int> (w));
        REP(i,h) REP(j,w) cin >> a[i][j];
        vector<vector<int>> b(x, vector<int> (y));
        REP(i,x) REP(j,y) cin >> b[i][j];

        // DEBUG(a);
        // DEBUG(b);

        vector<int> v1(2 * h * w);
        vector<int> v2(2 * h * w);

        REP(i,h) REP(j,w) v1[i * 2*w + j] = a[i][j];
        REP(i,x) REP(j,y) v2[(x - i - 1) * 2*w + (y - j - 1)] = b[i][j];

        // DEBUG(v1);
        // DEBUG(v2);

        auto r0 = ntt0.multiply(v1, v2);
        auto r1 = ntt1.multiply(v1, v2);

        // cerr << "res ids = ";
        REP(i,h) {
            REP(j,w) {
                int idx = (i + (x-1) / 2) * 2*w + (j + (y-1) / 2);
                // cerr << idx << ' ';
                CRT<int> crt;
                crt.add(MOD0, r0[idx]);
                crt.add(MOD1, r1[idx]);

                cout << crt.res << ' ';
            }
            cout << '\n';
        }
        cerr << endl;
    }
    return 0;
}
