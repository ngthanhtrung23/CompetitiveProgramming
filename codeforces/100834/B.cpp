
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
using namespace std;

const int MN = 100111;

struct Node {
	ll t;
	ll xk[5];
} it[MN * 8];

ll power(ll x, int k) {
	if (k == 0) return 1;
	if (k == 1) return x;
	if (k == 2) return x*x;
	if (k == 3) return x*x*x;
	if (k == 4) return power(x, 2) * power(x, 2);
	assert(0);
	return -1;
}

int a[MN];
ll C[11][11];

void up(int i) {
	assert(it[i].t == 0);
	FOR(k,0,4) {
		it[i].xk[k] = it[i<<1].xk[k] + it[i<<1|1].xk[k];
	}
}

void fix(int i, ll t) {
	ll xk[5];

	FOR(k,0,4) {         // xk[0] should be same
		xk[k] = 0;
		FOR(j,0,k) {
			xk[k] += C[k][j] * power(t,k-j) * it[i].xk[j];
		}
	}

	for(int k = 0; k <= 4; ++k)
		it[i].xk[k] = xk[k];
}

void down(int i) {
	if (it[i].t) {
		it[i<<1].t += it[i].t;
		it[i<<1|1].t += it[i].t;

		fix(i<<1, it[i].t);
		fix(i<<1|1, it[i].t);

		it[i].t = 0;
	}
}

void build(int i, int l, int r) {
	it[i].t = 0;
	if (l == r) {
		FOR(k,0,4) it[i].xk[k] = power(a[l], k);
		return ;
	}
	int mid = (l + r) >> 1;
	build(i<<1, l, mid);
	build(i<<1|1, mid+1, r);
	up(i);
}

void update(int i, int l, int r, int u, int v, int val) {
	if (v < l || r < u) return ;
	if (u <= l && r <= v) {
		it[i].t += val;
		fix(i, val);
		return ;
	}
	int mid = (l + r) >> 1;
	down(i);
	update(i<<1, l, mid, u, v, val);
	update(i<<1|1, mid+1, r, u, v, val);
	up(i);
}

ll get(int i, int l, int r, int u, int v, ll a[]) {
	if (v < l || r < u) return 0;
	if (u <= l && r <= v) {
		ll res = 0;

		FOR(k,0,4) {
			// sum(x^k) * a[4-k]
			res += it[i].xk[k] * a[4-k];
		}

		return res;
	}
	int mid = (l + r) >> 1;
	down(i);

	ll res = get(i<<1, l, mid, u, v, a)
		+ get(i<<1|1, mid+1, r, u, v, a);

	return res;
}

int main() {
	FOR(i,0,4) {
		FOR(j,0,i) {
			if (j == 0) C[i][j] = 1;
			else C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
	int n;
	while (scanf("%d\n", &n) == 1) {
		FOR(i,1,n) assert(scanf("%d", &a[i]) == 1);
		memset(it, 0, sizeof it);

		build(1, 1, n);

		int q; assert(scanf("%d", &q) == 1);
		while (q--) {
			int typ; assert(scanf("%d", &typ) == 1);
			if (typ == 1 || typ == 2) {
				int u, v; assert(scanf("%d%d", &u, &v) == 2);
				if (typ == 1) update(1, 1, n, u, v, -1);
				else update(1, 1, n, u, v, +1);
			}
			else {
				int u, v;
				ll a[5];
				assert(scanf("%d%d%lld%lld%lld%lld%lld", &u, &v, &a[0], &a[1], &a[2], &a[3], &a[4]) == 7);
				printf("%lld\n", get(1, 1, n, u, v, a));
			}
		}
		puts("");
	}
}
