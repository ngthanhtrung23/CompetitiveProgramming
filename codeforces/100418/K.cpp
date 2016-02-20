
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
	int n;
	while (cin >> n) {
		double best = 1.0 / (double) n;
		int save = 0;
		FOR(x,1,n-1) {
			double cur = 0.0;
			FOR(i,x,n-1) cur += x / (double) i;

			if (cur > best) {
				best = cur;
				save = x;
			}
		}
		cout << save << endl;
	}
}
