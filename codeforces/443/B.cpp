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

char s[10111];
int l, k;

bool check(int len) {
	FOR(i,0,l+k-len) {
		bool good = true;
		int j = i + len - 1;
		for(int u = i, v = i + len/2; v < j; ++u, ++v) {
			if (s[u] != '?' && s[v] != '?' && s[u] != s[v]) {
				good = false;
				break;
			}
		}
		if (good) return true;
	}
	return false;
}

int main() {
	// ios :: sync_with_stdio(false);
	while (gets(s)) {
		scanf("%d\n", &k);
		l = strlen(s);
		FOR(i,l,l+k) s[i] = '?';
		// PR0(s, l+k);

		int save = 0;
		FORD(res,l+k,1) if (res % 2 == 0) {
			if (check(res)) {
				save = res;
				break;
			}
		}
		cout << save << endl;
	}
	return 0;
}
