
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

const int MN = 14;
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

ll f[TWO(14)][15][100];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	int n, m, k;
	while (cin >> n >> m >> k) {
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;

		REP(mask,TWO(n)-1)
		FOR(good,0,k)
			FOR(inv,0,m) if (f[mask][good][inv]) {
				REP(next,n) if (!CONTAIN(mask,next)) {
					int placed = __builtin_popcount(mask);
					int good2 = good;
					if (next == placed) ++good2;
					int inv2 = inv;
					FOR(i,next+1,n-1) if (CONTAIN(mask,i)) ++inv2;

					f[mask + TWO(next)][good2][inv2] += f[mask][good][inv];
				}
			}

		cout << f[TWO(n) - 1][k][m] << endl;
	}
}
