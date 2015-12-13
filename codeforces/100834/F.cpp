
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

const int MN = 22;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	int n, k;
	while (cin >> n >> k) {
		if (n <= 9) {
			cout << n * (n-1) / 2 << endl;
			FOR(i,1,n) FOR(j,i+1,n) {
				cout << i << ' ' << j << endl;
			}
		}
		else {
			cout << 4*n << endl;
			FOR(turn,1,4) {
				FOR(i,1,n) {
					int j = (i + turn) % n;
					if (j == 0) j = n;
					cout << i << ' ' << j << endl;
				}
			}
		}
	}
}
