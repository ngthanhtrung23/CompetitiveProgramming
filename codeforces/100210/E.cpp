
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

ll MOD;
struct Matrix {
    ll x[2][2];
} I, A[66];

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,2) REP(j,2) {
        res.x[i][j] = 0;
        REP(k,2)
            res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return res;
}

void init() {
    I.x[0][0] = I.x[1][1] = 1;
    A[0].x[0][1] = A[0].x[1][0] = A[0].x[1][1] = 1;
    FOR(i,1,60) A[i] = A[i-1] * A[i-1];
}

ll fibo(ll k) {
    if (k == 0) return 0;
    if (k == 1) return 1;
    Matrix at = I;

    for(int i = 0; i < 40; ++i)
        if ((k >> i) & 1)
            at = at * A[i];
    return at.x[0][1];
}

ll f[1000111];
map< pair<ll,ll>, ll> id;

ll solve() {
    id.clear();
    const int C = 120000;
    FOR(i,1,C) {
        f[i] = fibo(i);
    }
    FOR(i,1,C-1) {
        if (f[i] == 0 && f[i+1] == 1) {
            return i;
        }
    }
    // map 0 --> sqrt
    FOR(i,0,C-1) {
        id[ make_pair(f[i], f[i+1]) ] = i;
    }
    // jump
    for(int i = C; ; i += C) {
        pair<ll,ll> cur = make_pair( fibo(i), fibo(i+1) );
        if (id.count(cur)) {
            ll someCycle = i - id[cur];
            ll res = someCycle;

            for(ll x = 1; x*x <= someCycle; ++x)
                if (someCycle % x == 0) {
                    if (fibo(x) == 0 && fibo(x+1) == 1)
                        res = min(res, x);

                    ll y = someCycle / x;
                    if (fibo(y) == 0 && fibo(y+1) == 1)
                        res = min(res, y);
                }

            return res;
        }
    }
    return -1;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);

    while (cin >> MOD) {
        init();
        cout << solve() << endl;
    }
}

