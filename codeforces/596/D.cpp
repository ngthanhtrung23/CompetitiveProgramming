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

const int MN = 2011;

double f[MN][MN][2][2], p;
bool visited[MN][MN][2][2];
int n, x[MN], h;
double p2, p12;

double get(int i, int j, int b1, int b2) {
	if (i > j) return 0;
	int left = x[i-1], right = x[j+1];
	if (b1 == 1) left += h;
	if (b2 == 0) right -= h;

	if (left > right) return 0;

	if (visited[i][j][b1][b2]) return f[i][j][b1][b2];
	visited[i][j][b1][b2] = 1;

	if (left > x[i]) return f[i][j][b1][b2] = get(i+1, j, 1, b2) + min(right, x[i] + h) - left;
	if (right < x[j]) return f[i][j][b1][b2] = get(i, j-1, b1, 0) + right - max(left, x[j] - h);

	double res = 0.0;

	if (i == j) {
		res = p * min(h, x[i] - left)
			+ (1-p) * min(h, right - x[i]);
	}
	else {
		res = p2  * (min(h, x[i] - left) + get(i+1, j, 0, b2))
			+ p12 * (min(h, right - x[i]) + get(i+1, j, 1, b2))
			+ p2  * (min(h, x[j] - left) + get(i, j-1, b1, 0))
			+ p12 * (min(h, right - x[j]) + get(i, j-1, b1, 1));
	}

	return f[i][j][b1][b2] = res;
}

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
	while (cin >> n >> h >> p) {
		p2 = p / 2;
		p12 = (1 - p) / 2;
		FOR(i,1,n) cin >> x[i];
		sort(x+1, x+n+1);

		x[0] = -1000111000;
		x[n+1] = -x[0];
		memset(visited, 0, sizeof visited);
		memset(f, 0, sizeof f);
		cout << get(1, n, 0, 1) << endl;
	}
}
