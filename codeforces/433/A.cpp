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

int main() {
	ios :: sync_with_stdio(false);
	int n, x, y;
	while (cin >> n) {
		x = y = 0;
		FOR(i,1,n) {
			int a; cin >> a;
			if (a == 100) ++x;
			else ++y;
		}
		bool ok = false;
		FOR(x1,0,x) FOR(y1,0,y) {
			int x2 = x - x1, y2 = y - y1;
			if (x1 + 2*y1 == x2 + 2*y2) {
				ok = true;
			}
		}
		if (ok) puts("YES"); else puts("NO");
	}
	return 0;
}
