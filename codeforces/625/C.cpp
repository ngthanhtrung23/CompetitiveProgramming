
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

int n, k, a[555][555];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n >> k) {
		int last = n * n;
		FOR(i,1,n) {
			FORD(j,n,k) {
				a[i][j] = last--;
			}
		}
		FOR(i,1,n) {
			FORD(j,k-1,1) a[i][j] = last--;
		}
		int sum = 0;
		FOR(i,1,n) sum += a[i][k];
		cout << sum << endl;
		FOR(i,1,n) {
			FOR(j,1,n) printf("%d ", a[i][j]);
			puts("");
		}
	}
}
