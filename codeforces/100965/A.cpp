#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int n;
int h[1000111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(15);
	freopen("alpinism.in", "r", stdin);
	freopen("alpinism.out", "w", stdout);

	int H;
	while (scanf("%d%d", &H, &n) == 2) {
		FOR(i,1,n) scanf("%d", &h[i]);
		h[++n] = H;
		h[0] = 0;

		double res = 0.0;
		FOR(i,0,n-1) {
			res = max(res + h[i+1] - (double) h[i] - res / 2.0, res);
		}
		cout << res << endl;
	}
}
