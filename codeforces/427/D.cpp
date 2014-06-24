#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int oo = 1000111;
const int MN = 5011;
char s[2][MN];
int faa[MN][MN], fab[MN][MN], fbb[MN][MN];
int ga[MN], gb[MN];

int main() {
	ios :: sync_with_stdio(false);
	while (gets(s[0])) {
		gets(s[1]);
		int l0 = strlen(s[0]), l1 = strlen(s[1]);

		memset(faa, 0, sizeof faa);
		memset(fab, 0, sizeof fab);
		memset(fbb, 0, sizeof fbb);

		// faa(i,j) = max(len | s[0][i..i+len-1] == s[0][j..j+len-1])
		FORD(i,l0-1,0) FORD(j,l0-1,i+1) {
			faa[i][j] = (s[0][i] == s[0][j]) ? faa[i+1][j+1] + 1 : 0;
			faa[j][i] = faa[i][j];
		}
		// fbb(i,j) = max(len | s[1][i..i+len-1] == s[1][j..j+len-1])
		FORD(i,l1-1,0) FORD(j,l1-1,i+1) {
			fbb[i][j] = (s[1][i] == s[1][j]) ? fbb[i+1][j+1] + 1 : 0;
			fbb[j][i] = fbb[i][j];
		}
		// fab(i,j) = max(len | s[0][i..i+len-1] == s[1][j..j+len-1])
		FORD(i,l0-1,0) FORD(j,l1-1,0) {
			fab[i][j] = (s[0][i] == s[1][j]) ? fab[i+1][j+1] + 1 : 0;
		}
		// ga(i) = shortest length such that the substring of s[0] starts at i occurs only once
		REP(i,l0) {
			ga[i] = 1;
			REP(j,l0) if (i != j)
				ga[i] = max(ga[i], faa[i][j]+1);
		}
		// PR0(ga, l0);
		// gb(i) = shortest length such that the substring of s[1] starts at i occurs only once
		REP(i,l1) {
			gb[i] = 1;
			REP(j,l1) if (i != j)
				gb[i] = max(gb[i], fbb[i][j]+1);
		}
		// PR0(gb, l1);

		int res = oo;
		REP(i,l0) REP(j,l1) {
			int cur = max(ga[i], gb[j]);
			if (i + cur > l0 || j + cur > l1) continue;
			if (cur > fab[i][j]) continue;

			res = min(res, cur);

			// if (res == 7) cout << i << ' ' << j << ' ' << fab[i][j] << endl;
		}
		if (res == oo) res = -1;
		cout << res << endl;
	}
	return 0;
}
