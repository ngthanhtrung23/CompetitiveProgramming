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

const int MN = 1000111;
const ll MOD = 1e9 + 7;
int n;
ll k[MN], a[MN];

int read() {
	int x; assert(scanf("%d", &x));
	return x;
}

ll sum1(ll n) {
	return (n * (n + 1) / 2) % MOD;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (scanf("%d", &n) == 1) {
		ll suma = 0, sumk = 0;
		FOR(i,1,n) {
			k[i] = read();
			a[i] = read();

			suma += a[i] * k[i];
			sumk += k[i];
		}
		ll each = suma / sumk;
//		DEBUG(each);

		ll res = 0, less = 0, more = 0;
		FOR(i,1,n) {
			if (a[i] == each) {
				res = (res + less % MOD * k[i]) % MOD;
				res = (res + more % MOD * k[i]) % MOD;
			}
			else if (a[i] < each) {
//				cout << "a[i] < each" << endl;
				ll delta = each - a[i];
				ll need = delta * k[i];
				ll can = min(more, need);

				if (can == need) {
					res = (res + sum1(k[i]) * delta) % MOD;
				}
				else {
					ll lastFullCol = can / delta;
					ll lastColHeight = can % delta;

					// move to left
					res = (res + sum1(lastFullCol) * delta) % MOD;
					res = (res + (lastFullCol + 1) * lastColHeight) % MOD;
//					DEBUG(res);

					// move to right
					if (k[i] > lastFullCol + 1) {
						ll dist = k[i] - (lastFullCol + 2);
						res = (res + sum1(dist) * delta) % MOD;
					}
					res = (res + (delta - lastColHeight) * (k[i] - lastFullCol - 1)) % MOD;
				}

				more -= can;
				need -= can;

				res = (res + more % MOD * k[i]) % MOD;
				res = (res + less % MOD * k[i]) % MOD;

				less += need;
			}
			else { // a[i] > each
//				cout << "a[i] > each" << endl;
				ll delta = a[i] - each;
				ll need = delta * k[i];
				ll can = min(less, need);

				if (can == need) {
					res = (res + sum1(k[i]) * delta) % MOD;
				}
				else {
					ll lastFullCol = can / delta;
					ll lastColHeight = can % delta;

					// move to left
					res = (res + sum1(lastFullCol) * delta) % MOD;
					res = (res + (lastFullCol + 1) * lastColHeight) % MOD;
//					DEBUG(res);

					// move to right
					if (k[i] > lastFullCol + 1) {
						ll dist = k[i] - (lastFullCol + 2);
						res = (res + sum1(dist) * delta) % MOD;
					}
					res = (res + (delta - lastColHeight) * (k[i] - lastFullCol - 1)) % MOD;
				}

				less -= can;
				need -= can;

				res = (res + more % MOD * k[i]) % MOD;
				res = (res + less % MOD * k[i]) % MOD;

				more += need;
			}
			assert(more == 0 || less == 0);
//			DEBUG(res);
		}
		cout << res << endl;
	}
}
