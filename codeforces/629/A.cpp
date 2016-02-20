
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
char a[111][111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
		int res = 0;
		FOR(i,1,n) FOR(j,1,n) if (a[i][j] == 'C') {
			FOR(ii,i+1,n) if (a[ii][j] == 'C') ++res;
			FOR(jj,j+1,n) if (a[i][jj] == 'C') ++res;
		}
		cout << res << endl;
	}
}
