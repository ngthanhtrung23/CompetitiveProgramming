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

string s;
int n, m;

bool check(int l, int r) {
	FOR(start,l,r) {
		if (s.substr(start, 7) == "desmond") return true;
	}
	return false;
}

int get() {
	int res = -1;
	if (check(0, n-6)) res = 0;
	FOR(i,1,m) {
		int u; char c; cin >> u >> c; --u;
		s[u] = c;
		if (check(max(0,u-10), min(u,n-6)) && res < 0) {
			res = i;
		}
	}
	return res;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> s) {
		n = s.length();
		cin >> m;
		int res = get();
		if (res < 0) puts("Goodbye, my love!");
		else {
			puts("I love you, Desmond!");
			printf("%d\n", res);
		}
	}
	return 0;
}
