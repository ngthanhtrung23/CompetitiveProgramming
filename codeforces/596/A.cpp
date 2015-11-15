
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
	int n;
	while (cin >> n) {
		int x[5], y[5];
		FOR(i,1,n) cin >> x[i] >> y[i];

		int min_x = *min_element(x+1, x+n+1);
		int max_x = *max_element(x+1, x+n+1);
		int min_y = *min_element(y+1, y+n+1);
		int max_y = *max_element(y+1, y+n+1);

		if (min_x != max_x && min_y != max_y) cout << (max_x - min_x) * (max_y - min_y);
		else cout << -1;
		cout << endl;
	}
}
