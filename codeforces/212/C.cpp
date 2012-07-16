#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;
const double PI = acos(-1.0);

string s;
int n, var[111], zero[111], k;
bool need[111][111];
long long f[111][2][2];

int main() {
	cin >> s;
	n = s.length();
	s = ' ' + s + s[0];

	var[1] = 1;
	FOR(i,2,n) {
		if (s[i] == 'A' && s[i-1] == 'B') {
			var[i] = var[i-1];
		}
		else var[i] = var[i-1] + 1;
	}
	if (s[1] == 'A' && s[n] == 'B') {
		int t = n;
		while (t > 1 && var[t-1] == var[n]) --t;
		FOR(i,t,n) var[i] = var[1];
	}
	// FOR(i,1,n) cout << var[i] << ' '; cout << endl;
	int k = 0;
	FOR(i,1,n) k = max(k, var[i]);

	var[n+1] = var[1];

	FOR(i,1,n) {
		if (s[i] == 'A' && s[i+1] == 'A') zero[var[i+1]] = 1;
		if (s[i] == 'B' && s[i+1] == 'B') zero[var[i]] = 1;
	}
	// FOR(i,1,k) cout << zero[i] << ' '; cout << endl;

	FOR(i,1,n) {
		if (s[i] == 'A' && s[i+1] == 'B') {
			need[var[i]][var[i+1]] = need[var[i+1]][var[i]] = true;
			// cout << var[i] << ' ' << var[i+1] << endl;
		}
	}
	f[1][0][0] = 1;
	if (!zero[1]) f[1][1][1] = 1;
	FOR(i,2,k) REP(first,2) {
		if (!zero[i]) f[i][first][1] = f[i-1][first][1] + f[i-1][first][0];

		f[i][first][0] = f[i-1][first][1];
		if (!need[i][i-1]) f[i][first][0] += f[i-1][first][0];
	}
	long long res = f[k][1][1] + f[k][1][0] + f[k][0][1];
	if (!need[1][k]) res += f[k][0][0];
	cout << res << endl;
    return 0;
}
