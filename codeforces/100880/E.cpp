#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define double long double
#define int long long
using namespace std;

const int MN = 5000111; // 10*MN
const int MOD = 1000000007;
const double PI = acos((double) -1.0);

typedef complex<double> cplex;
int rev[MN];
cplex wlen_pw[MN], fa[MN], fb[MN];

void fft(cplex a[], int n, bool invert) {
	for (int i = 0; i < n; ++i) if (i < rev[i]) swap (a[i], a[rev[i]]);

	for (int len = 2; len <= n; len <<= 1) {
		double alpha = 2 * PI / len * (invert ? -1 : +1);
		int len2 = len >> 1;

		wlen_pw[0] = cplex(1, 0);
		cplex wlen(cos(alpha), sin(alpha));
		for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i-1] * wlen;

		for (int i = 0; i < n; i += len) {
			cplex t, *pu = a+i, *pv = a + i + len2,
					*pu_end = a + i + len2, *pw = wlen_pw;
			for (; pu != pu_end; ++pu, ++pv, ++pw) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}

	if (invert) REP(i, n) a[i] /= n;
}

void calcRev(int n, int logn) {
	REP(i, n) {
		rev[i] = 0;
		REP(j, logn) if (i & (1 << j)) rev[i] |= 1 << (logn - 1 - j);
	}
}

void mulpoly(int a[], int b[], ll c[], int na, int nb, int &n) {
	int l = max(na, nb), logn = 0;
	for (n = 1; n < l; n <<= 1) ++logn;
	n <<= 1; ++logn;
	calcRev(n, logn);

	REP(i,n) fa[i] = fb[i] = cplex(0);
	REP(i,na) fa[i] = cplex(a[i]);
	REP(i,nb) fb[i] = cplex(b[i]);

	fft(fa, n, false);
	fft(fb, n, false);

	REP(i,n) fa[i] *= fb[i];
	fft(fa, n, true);

	REP(i,n) c[i] = (ll)(fa[i].real() + 0.5);
}

int n, k, l;
vector<int> V;
int x[MN];
int a[MN], b[MN];
ll c[MN];
ll inv[MN / 2];
string s;

ll power(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    ll mid = power(x, k >> 1);
    mid = (mid * mid) % MOD;
    
    if (k & 1) return mid * x % MOD;
    return mid;
}

void add(ll &x, ll y) {
	x += y;
	if (x >= MOD) x -= MOD;
}

int solve() {
	V.clear();
	REP(i,l) if (s[i] == '1') V.push_back(i);
	REP(i,n-1) {
		a[i] = V[i + 1] - V[i];
	}
	a[n-1] = V[0] + l - V[n-1];
	REP(i,n) {
		b[i] = a[n - 1 - i];
		b[i + n] = a[n - 1 - i];
	}
	int m = 0;

	mulpoly(a, b, c, n, n + n, m);
	ll run = 1;

	ll res = (c[n - 1] % MOD);
	for(int i = k; i > 0; i--) {
		run = run * i % MOD * inv[i + n - k] % MOD;
		add(res, run * (c[n + k - i] % MOD) * 2 % MOD);
	}

	res = (res * inv[l] % MOD * inv[4]) % MOD;
    return res;
}

void init() {
	for(int i = 0; i <= 1000000; i++) inv[i] = power(i, MOD - 2);
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0); cin.tie(0);
    init();

    int ntest; cin >> ntest;
    FOR(test,1,ntest){
        cin >> n >> k >> l;
        cin >> s;
    	cout << "Case #" << test << ": " << solve() << endl;
        cerr << test << endl;
    }
    return 0;
}
