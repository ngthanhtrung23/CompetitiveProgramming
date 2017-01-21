#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MOD = 1e9 + 7;
int n, m;
int R[2011];

int power(int x, int k) {
	int res = 1;
	while (k > 0) {
		if (k & 1) res = res * x % MOD;
		k >>= 1;
		x = x * x % MOD;
	}
	return res;
}

int inverse(int x) {
	return power(x, MOD - 2);
}

int gt_small[1000111];
int inv_small[1000111];
int T;

int C(int n, int k) {
	if (T >= 0) {
		int res = 1;
		FOR(i,n-k+1,n)
			res = res * i % MOD;
		res = res * inv_small[k] % MOD;
		return res;
	}
	else {
		return gt_small[n]
			* (inv_small[k]) % MOD
			* (inv_small[n-k]) % MOD;
	}
}

int cnt[1011], cnt1[1011];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

	gt_small[0] = 1;
	FOR(i,1,1000*1000) gt_small[i] = gt_small[i-1] * i % MOD;
	FOR(i,0,1000*1000) inv_small[i] = inverse(gt_small[i]);

	int ntest; GI(ntest);
	FOR(test,1,ntest) {
		GI(n); GI(m);
		FOR(i,1,n) GI(R[i]);

		int res = 0;
		if (n == 1) {
			res = m;
		}
		else {
			T = m - 1; FOR(i,1,n) T -= 2*R[i]; 

			int h = *max_element(R+1, R+n+1);
			assert(h <= 50);
			int ln = n + (h * 2);

			memset(cnt1, 0, sizeof cnt1);
			memset(cnt, 0, sizeof cnt);
			FOR(i,1,n) cnt1[R[i]]++;

			FOR(h1,1,h) FOR(h2,h1,h) if (cnt1[h1] && cnt1[h2]) {
				int c1 = cnt1[h1];
				int c2 = cnt1[h2];
				if (h1 == h2) cnt[h1 + h2] += c1 * (c1 - 1) / 2;
				else cnt[h1 + h2] += c1 * c2;
			}

			FOR(sum,0,h*2) if (cnt[sum]) {
				int X = T + sum;
                if (X < 0) continue;

				int tmp = 2 * gt_small[n-2] * C(X+n, n) % MOD;

				res = (res + cnt[sum] * tmp) % MOD;
			}
		}

		cout << "Case #" << test << ": " << res << '\n';
	}
}
