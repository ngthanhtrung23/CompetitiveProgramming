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

char a[4][1011];
int l[4];

bool check(int i) {
	bool ok = true;
	// l[i]*2 <= l[j]
	REP(j,4) if (j != i && l[i]*2 > l[j]) ok = false;
	if (ok) return true;

	ok = true;
	// l[i] >= 2*l[j]
	REP(j,4) if (j != i && l[j]*2 > l[i]) ok = false;
	if (ok) return true;

	return false;
}

int main() {
	ios :: sync_with_stdio(false);
	while (gets(a[0])) {
		FOR(i,1,3) gets(a[i]);
		REP(i,4) l[i] = strlen(a[i]) - 2;
		int best = 2, cnt = 0;

		REP(i,4) {
			if (check(i)) {
				best = i;
				++cnt;
			}
		}
		if (cnt > 1) best = 2;

		cout << (char) ('A' + best) << endl;
	}
	return 0;
}
