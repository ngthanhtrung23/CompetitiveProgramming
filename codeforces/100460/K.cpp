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

const int MN = 100111;
const int oo = 1000111000;

int nSpell, nDay;
long long a[2][MN];
int res[2][MN];

int get(int turn, int val) {
	if (val >= a[turn][nSpell]) return oo;

	int l = 1, r = nSpell, res = nSpell;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (a[turn][mid] > val) {
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return res;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> nSpell) {
		REP(turn,2) {
			FOR(i,1,nSpell) {
				cin >> a[turn][i];
				a[turn][i] = max(a[turn][i], a[turn][i-1]);
			}
		}
		cin >> nDay;
		REP(turn,2) FOR(i,1,nDay) {
			int b; cin >> b;
			res[turn][i] = get(turn, b);
		}
		FOR(i,1,nDay) {
			if (res[0][i] == res[1][i]) puts("Draw");
			else if (res[0][i] > res[1][i]) puts("Constantine");
			else puts("Mike");
		}
	}
	return 0;
}
