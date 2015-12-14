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

const int MN = 1011;

double bad[MN], f[MN], p[MN][MN];
bool done[MN];
int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);

	while (scanf("%d", &n) == 1) {
		FOR(i,1,n) FOR(j,1,n) {
			int t; scanf("%d", &t);
			p[i][j] = t / (double) 100.0;
			if (i == j) p[i][j] = 1.0;
		}
		f[n] = 0.0;
		FOR(i,1,n-1) {
			bad[i] = 1 - p[i][n];
			f[i] = (double) 1.0 / p[i][n];
		}
		memset(done, 0, sizeof done);
		done[n] = true;

		FOR(turn,1,n-1) {
			int best = -1;
			FOR(i,1,n) if (!done[i]) {
				if (best < 0 || f[i] < f[best]) best = i;
			}
			done[best] = true;

			FOR(i,1,n) if (!done[i] && p[i][best] > 1e-9) {
				if (fabs(1 - bad[i]) < 1e-9) {
					f[i] = (p[i][best] * f[best] + 1) / p[i][best];
					bad[i] = 1 - p[i][best];
				}
				else {
					double S = f[i] * (1 - bad[i]) - bad[i];
					double bad2 = bad[i] * (1 - p[i][best]);
					double f2 = (S + bad[i] * p[i][best] * (f[best] + 1) + bad2) / (1 - bad2);

					bad[i] = bad2;
					f[i] = f2;
				}
				if (bad[i] < 1e-90) bad[i] = 0;
			}
//			PR(f, n);
		}
		cout << f[1] << endl;
	}
}
