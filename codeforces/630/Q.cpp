
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

double solve3(double a) {
	double S = sqrt(3.0) * a * a / 4.0;
	double h = 2 * S / a;
	double AO = 2 * h / 3;

	double h3 = sqrt(a * a - AO * AO);
	return h3 * S / 3.0;
}
double solve4(double a) {
	double AO = sqrt(a*a + a*a) / 2;
	double h4 = sqrt(a * a - AO * AO);
	double S = a * a;

	return h4 * S / 3.0;
}
double solve5(double a) {
	double S = 0.25 * sqrt(5 * (5 + 2*sqrt(5))) * a * a;
	double AO = sqrt(50 + 10*sqrt(5)) * a / 10.0;
	double h5 = sqrt(a * a - AO * AO);
	
	return h5 * S / 3.0;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(12);
	double l3, l4, l5;
	cin >> l3 >> l4 >> l5;

	cout << solve3(l3) + solve4(l4) + solve5(l5) << endl;
}
