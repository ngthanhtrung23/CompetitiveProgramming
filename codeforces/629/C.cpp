
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

const int MOD = 1e9 + 7;
const int MN = 2011;
int f[MN][MN][2];
string s;
int m, n;

void update(int& x, int val) {
	x += val;
	if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n >> m) {
		cin >> s;
		int need = n - m + 1;

		int pref = 0, minpref = 0;
		for(char c : s) {
			if (c == '(') ++pref;
			else --pref;
			minpref = min(minpref, pref);
		}
//		DEBUG(minpref);
//		DEBUG(pref);

		memset(f, 0, sizeof f);
		f[0][0][0] = 1;

		FOR(i,0,need-1) FOR(sum,0,2000) REP(t,2) {
			int cur = f[i][sum][t];
			if (!cur) continue;

			// add (
			if (sum < 2000) {
				update(f[i+1][sum+1][t], cur);
			}
			// add )
			if (sum > 0) {
				update(f[i+1][sum-1][t], cur);
			}
			// add s
			if (t == 0 && sum + minpref >= 0 && sum + pref <= 2000) {
				update(f[i+1][sum + pref][1], cur);
			}
		}
		cout << f[need][0][1] << endl;
	}
}
