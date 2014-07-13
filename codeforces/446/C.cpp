#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 300111;
const long long MOD = 1000000009;

struct Matrix {
	int m, n;
	long long x[3][3];
} matf[30], mats[30], I[4];

struct Node {
	long long sum, f0, f1;
} it[MN * 6];
long long a[MN];

Matrix operator * (const Matrix &a, const Matrix &b) {
	Matrix c; c.m = a.m; c.n = b.n;
	REP(i,c.m) REP(j,c.n) {
		c.x[i][j] = 0;
		REP(k,a.n) {
			c.x[i][j] += a.x[i][k] * (long long) b.x[k][j];
		}
		c.x[i][j] %= MOD;
	}
	return c;
}

int cache[1000111];

void initMatrix() {
	REP(t,4) {
		I[t].m = I[t].n = t;
		REP(i,t) REP(j,t)
			if (i == j) I[t].x[i][j] = 1;
			else I[t].x[i][j] = 0;
	}

	matf[0].m = matf[0].n = 2;
	matf[0].x[0][0] = 0; matf[0].x[0][1] = 1;
	matf[0].x[1][0] = 1; matf[0].x[1][1] = 1;

	mats[0].m = mats[0].n = 3;
	mats[0].x[0][0] = 0; mats[0].x[0][1] = 1; mats[0].x[0][2] = 0;
	mats[0].x[1][0] = 1; mats[0].x[1][1] = 1; mats[0].x[1][2] = 0;
	mats[0].x[2][0] = 1; mats[0].x[2][1] = 1; mats[0].x[2][2] = 1;

	FOR(i,1,29) {
		matf[i] = matf[i-1] * matf[i-1];
		mats[i] = mats[i-1] * mats[i-1];
	}

	REP(u,1000000) {
		REP(i,20) if (u & (1<<i)) {
			cache[u] = i;
			break;
		}
	}
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

Matrix cachePower[3][300111];
bool hasCache[3][300111];

Matrix power(int t, int k) {
	if (hasCache[t][k]) return cachePower[t][k];
	hasCache[t][k] = true;

	Matrix res;
	if (t == 0) res = I[matf[0].m];
	else res = I[mats[0].m];

	int savek = k;

	while (k) {
		int i = cache[k];
		k -= 1<<i;
		if (t == 0) res = res * matf[i];
		else res = res * mats[i];
	}
	cachePower[t][savek] = res;
	return res;
}

inline long long add(long long x, long long y) {
	long long res = x + y;
	if (res >= MOD) res -= MOD;
	return res;
}

void init(int i, int l, int r) {
	if (l == r) {
		it[i].sum = a[l];
		it[i].f0 = it[i].f1 = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	init(CT(i), l, mid);
	init(CP(i), mid+1, r);

	it[i].sum = add(it[CT(i)].sum, it[CP(i)].sum);
}

Matrix cur;
inline long long getSum(long long f0, long long f1, int k) {
	cur = power(1, k);
	return ((cur.x[2][0] * f0 + cur.x[2][1] * f1) % MOD + cur.x[2][2] * (f0 + f1)) % MOD;
}

inline void put(int i, int l, int r, long long f0, long long f1) {
	if (l == r) {
		it[i].sum = add(it[i].sum, f0);
	} else {
		it[i].sum = add(it[i].sum, getSum(f0, f1, r - l - 1));
		it[i].f0 = add(it[i].f0, f0);
		it[i].f1 = add(it[i].f1, f1);
	}
}

inline pair<long long, long long> getK(long long f0, long long f1, int k) {
	if (k == 0) return make_pair(f0, f1);

	cur = power(0, k);
	return make_pair(
		(cur.x[0][0] * f0 + cur.x[0][1] * f1) % MOD,
		(cur.x[1][0] * f0 + cur.x[1][1] * f1) % MOD
	);
}

void down(int i, int l, int r, int mid) {
	if (it[i].f0 || it[i].f1) {
		pair<long long, long long> ff = getK(it[i].f0, it[i].f1, mid-l+1);

		put(CT(i), l, mid, it[i].f0, it[i].f1);
		put(CP(i), mid+1, r, ff.first, ff.second);

		it[i].f0 = it[i].f1 = 0;
	}
}

void update(int i, int l, int r, int u, int v) {
	if (v < l || r < u) return ;
	if (u <= l && r <= v) {
		pair<long long, long long> ff = getK(1, 1, l-u);
		put(i, l, r, ff.first, ff.second);
		return ;
	}
	int mid = (l + r) >> 1;
	down(i, l, r, mid);

	update(CT(i), l, mid, u, v);
	update(CP(i), mid+1, r, u, v);

	it[i].sum = add(it[CT(i)].sum, it[CP(i)].sum);
}

long long get(int i, int l, int r, int u, int v) {
	if (v < l || r < u) return 0;
	if (u <= l && r <= v) return it[i].sum;

	int mid = (l + r) >> 1;
	down(i, l, r, mid);
	return add(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
}

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

int main() {
	initMatrix();

	int n, q;
	GN(n); GN(q);
	FOR(i,1,n) GN(a[i]);
	memset(it, 0, sizeof it);
	init(1, 1, n);

	while (q--) {
		int typ, u, v;
		GN(typ); GN(u); GN(v);
		if (typ == 1) {
			update(1, 1, n, u, v);
		} else {
			printf("%d\n", (int) get(1, 1, n, u, v));
		}
	}
	return 0;
}
