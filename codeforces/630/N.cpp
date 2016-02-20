
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(12);
	double a, b, c;
	while (cin >> a >> b >> c) {
		double delta = b * b - 4 * a * c;
		double x1 = (-b + sqrt(delta)) / 2 / a;
		double x2 = (-b - sqrt(delta)) / 2 / a;
		cout << max(x1, x2) << endl << min(x1, x2) << endl;
	}
}
