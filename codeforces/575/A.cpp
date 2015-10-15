
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

const int MN = 50111;
ll MOD;

struct Matrix {
    ll x[2][2];

    void print() {
        REP(i,2) REP(j,2) cout << x[i][j] << ' ';
        cout << endl;
    }
} I, A, it[MN * 4];

bool operator == (const Matrix& a, const Matrix& b) {
    REP(i,2) REP(j,2) if (a.x[i][j] != b.x[i][j]) return false;
    return true;
}

ll k;
int n, m;
ll s[MN];
map<ll,ll> actual;

void init() {
    actual.clear();
    memset(it, 0, sizeof it);
}

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,2) REP(j,2) {
        res.x[i][j] = 0;
        REP(k,2)
            res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return res;
}
Matrix power(const Matrix& a, ll k) {
    if (k == 0) return I;
    if (k == 1) return a;
    Matrix mid = power(a*a, k >> 1);
    if (k & 1) return mid * a;
    return mid;
}
Matrix theMatrix(ll u) {
    if (u < 1) return I;
    Matrix res;
    res.x[0][0] = 0;
    res.x[0][1] = 1 % MOD;
    res.x[1][0] = (actual.count(u-1) ? actual[u-1] : s[(u-1) % n]) % MOD;
    res.x[1][1] = (actual.count(u) ? actual[u] : s[u % n]) % MOD;
    return res;
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].x[0][0] = 0;
        it[i].x[0][1] = 1 % MOD;
        it[i].x[1][0] = s[(l-1) % n] % MOD;
        it[i].x[1][1] = s[l % n] % MOD;
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i] = it[i<<1|1] * it[i<<1];
}

Matrix get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return I;
    if (u <= l && r <= v) {
        return it[i];
    }

    int mid = (l + r) >> 1;
    return get(i<<1|1, mid+1, r, u, v) * get(i<<1, l, mid, u, v);
}

Matrix get(ll from, ll to) {
    __typeof(actual.begin()) it = actual.lower_bound(from);
    assert(it == actual.end() || it->first > to);

    if (from > to) return I;
    if (from == to) return theMatrix(from);

    ll from_div = from / n, from_mod = from % n;
    if (from_mod == 0) from_mod = n, --from_div;

    ll to_div = to / n, to_mod = to % n;
    if (to_mod == 0) to_mod = n, --to_div;

    assert(from_div <= to_div);

    if (from_div == to_div) return get(1, 1, n, from_mod, to_mod);

    return get(1, 1, n, 1, to_mod)
        * power(get(1, 1, n, 1, n), to_div - from_div - 1)
        * get(1, 1, n, from_mod, n);
}

Matrix get_brute(int k) {
    Matrix res = I;
    FOR(i,1,k) res = theMatrix(i) * res;
    return res;
}

ll solve() {
//    Matrix t = get(1, 1, n, n-1, n);
//    Matrix t = get_brute(k); cout << "t = "; t.print();
    if (!actual.count(k)) actual[k] = s[k % n];

    A = I;
    ll cur = 0;
    while (cur < k) {
        __typeof(actual.begin()) it = actual.upper_bound(cur);
        ll id = it->first;
        A = get(cur+1, id-2) * A;
        cur = id-2;

//        DEBUG(cur);
//        t = get_brute(cur);
//        REP(_1,2) REP(_2,2) assert(t.x[_1][_2] == A.x[_1][_2]);

        A = theMatrix(cur+1) * A;
        ++cur;

        while (cur+1 <= k && (actual.count(cur) || actual.count(cur+1))) {
            A = theMatrix(cur+1) * A;
            ++cur;
        }
//        DEBUG(cur);
//        t = get_brute(cur);
//        REP(_1,2) REP(_2,2) assert(t.x[_1][_2] == A.x[_1][_2]);
    }
    return A.x[0][1];
}

int main() {
    ios :: sync_with_stdio(false);

    while (cin >> k >> MOD) {
        I.x[0][0] = I.x[1][1] = 1 % MOD;
        init();

        cin >> n;
        REP(i,n) {
            cin >> s[i];
            s[i] %= MOD;
        }

        cin >> m;
        FOR(i,1,m) {
            ll id, val;
            cin >> id >> val;
            val %= MOD;
            actual[id] = val;
        }
        build(1, 1, n);
        cout << solve() << endl;
    }
}

