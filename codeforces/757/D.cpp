
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int f[80][TWO(20) + 11], first[88];
int val[88][88];

const int MOD = 1e9 + 7;
void update(int& f, int x) {
	f += x;
	if (f >= MOD) f -= MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
	int n; string s;
	while (cin >> n >> s) {
		s = " " + s + " ";
		FOR(i,1,n) {
			FOR(j,i,n) {
				if (i == j) val[i][j] = s[i] - '0';
				else val[i][j] = val[i][j-1] * 2 + s[j] - '0';

				if (val[i][j] > 100) val[i][j] = 100;
			}
		}
		memset(f, 0, sizeof f);
		FOR(i,0,n-1) { f[i][0] = 1; }

		FORD(i,n,1) {
			if (i == n || s[i] == '1') first[i] = i;
			else first[i] = first[i+1];
		}

		FOR(i,0,n-1) REP(j,TWO(20)) {
			int cur = f[i][j];
			if (!cur) continue;

			FOR(ii,first[i+1],n) {
				int t = val[i+1][ii];
				if (t > 20) break;
				if (t > 0)
					update(f[ii][j | TWO(t-1)], cur);
			}
		}
		int res = 0;
		FOR(i,1,n) FOR(j,1,20) {
			update(res, f[i][TWO(j)-1]);
		}
		cout << res << endl;
	}
}
