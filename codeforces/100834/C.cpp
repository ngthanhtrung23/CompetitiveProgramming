
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
using namespace std;

const int MN = 111;
int a[111];
int n;

double cover(double r) {
	double sum = 0.0;
	FOR(i,1,n) {
		double c = (2*r*r - a[i]*(double) a[i]) / 2 / r / r;
		sum += acos(c);
	}
	return sum;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i];
		double res = -1.0;

		double l = *max_element(a+1, a+n+1) / 2.0;
		double r = 1e9;

		double PI = acos((double) -1.0);
		if (cover(l) >= 2*PI) {
			REP(turn,1000) {
				double mid = (l + r) / 2.0;
				if (cover(mid) >= 2*PI) {
					res = mid;
					l = mid;
				}
				else r = mid;
			}
		}

		if (res < 0) cout << -1 << endl;
		else cout << res << endl;
	}
}
