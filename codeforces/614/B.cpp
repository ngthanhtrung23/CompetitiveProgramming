
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

int n;
string a[100111];

bool good(const string& a) {
	if (a[0] != '1') return false;
	FOR(i,1,SZ(a) - 1) if (a[i] > '0') return false;
	return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		bool hasZero = false;
		FOR(i,1,n) {
			cin >> a[i];
			if (a[i] == "0") hasZero = true;
		}
		if (hasZero) {
			puts("0");
			continue;
		}
		int n0 = 0;
		bool has = false;
		FOR(i,1,n) {
			if (good(a[i])) {
				n0 += SZ(a[i]) - 1;
			}
			else {
				has = true;
				cout << a[i];
			}
		}
		if (!has) cout << '1';
		while (n0--) cout << '0'; cout << endl;
	}
}
