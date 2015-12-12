
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

#define x0 x0___
#define y0 y0___

const int MN = 511;
int visited[MN][MN];
int res[100111];
int x, y, x0, y0;

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};
int dc[333];

bool outside(int u, int v) {
	return u < 1 || u > x || v < 1 || v > y;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	dc['U'] = 0;
	dc['D'] = 1;
	dc['L'] = 2;
	dc['R'] = 3;

	while (cin >> x >> y >> x0 >> y0) {
		string s; cin >> s;
		memset(visited, 0, sizeof visited);
		memset(res, 0, sizeof res);
		visited[x0][y0] = 1; res[0] = 1;

		int u = x0, v = y0;
		int l = s.length();
		REP(i,l) {
			int dir = dc[s[i]];
			if (!outside(u + di[dir], v + dj[dir])) {
				u += di[dir];
				v += dj[dir];
			}
			if (!visited[u][v]) res[i+1] = 1;
			visited[u][v] = 1;
		}
		FOR(i,1,x) FOR(j,1,y) if (!visited[i][j]) ++res[l];
		FOR(i,0,l) cout << res[i] << ' '; cout << endl;
	}
}
