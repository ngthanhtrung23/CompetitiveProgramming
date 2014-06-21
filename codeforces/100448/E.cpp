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

int n, a[22];
set<int> s;

bool check1() {
	return a[1] == a[n];
}

bool check2() {
	if (s.size() <= 2) return true;
	if (s.size() == 3) {
		__typeof(s.begin()) it = s.begin();
		int u = *it;
		++it; int v = *it;
		++it; int w = *it;

		return w == u + v;
	}
	return false;
}

bool can[2000];

bool check3() {
	FOR(x,1,50) FOR(y,x+1,50) FOR(z,y+1,50) {
		can[x] = can[y] = can[z] = can[x+y] = can[x+z] = can[y+z] = can[x+y+z] = true;
		bool ok = true;
		FOR(i,1,n) if (!can[a[i]]) {
			ok = false;
			break;
		}
		can[x] = can[y] = can[z] = can[x+y] = can[x+z] = can[y+z] = can[x+y+z] = false;
		if (ok) {
			return true;
		}
	}
	return false;
}

bool check4() {
	FOR(x,1,50) FOR(y,x+1,50) FOR(z,y+1,50) FOR(t,z+1,50) {
		can[x] = can[y] = can[z] = can[t]
			= can[x+y] = can[x+z] = can[x+t] = can[y+z] = can[y+t] = can[z+t]
			= can[x+y+z] = can[x+y+t] = can[x+z+t] = can[y+z+t]
			= can[x+y+z+t] = true;
		bool ok = true;
		FOR(i,1,n) if (!can[a[i]]) {
			ok = false;
			break;
		}
		if (ok) return true;
		can[x] = can[y] = can[z] = can[t]
			= can[x+y] = can[x+z] = can[x+t] = can[y+z] = can[y+t] = can[z+t]
			= can[x+y+z] = can[x+y+t] = can[x+z+t] = can[y+z+t]
			= can[x+y+z+t] = false;
	}
	return false;
}

bool check5() {
	FOR(x,1,50) FOR(y,x+1,50) FOR(z,y+1,50) FOR(t,z+1,50) FOR(u,t+1,50) {
		can[x] = can[y] = can[z] = can[t]
			= can[x+y] = can[x+z] = can[x+t] = can[y+z] = can[y+t] = can[z+t]
			= can[x+y+z] = can[x+y+t] = can[x+z+t] = can[y+z+t]
			= can[x+y+z+t] = true;
		can[x+u] = can[y+u] = can[z+u] = can[t+u]
			= can[x+y+u] = can[x+z+u] = can[x+t+u] = can[y+z+u] = can[y+t+u] = can[z+t+u]
			= can[x+y+z+u] = can[x+y+t+u] = can[x+z+t+u] = can[y+z+t+u]
			= can[x+y+z+t+u] = true;
		can[u] = true;
		bool ok = true;
		FOR(i,1,n) if (!can[a[i]]) {
			ok = false;
			break;
		}
		if (ok) return true;
		can[x] = can[y] = can[z] = can[t]
			= can[x+y] = can[x+z] = can[x+t] = can[y+z] = can[y+t] = can[z+t]
			= can[x+y+z] = can[x+y+t] = can[x+z+t] = can[y+z+t]
			= can[x+y+z+t] = false;
		can[x+u] = can[y+u] = can[z+u] = can[t+u]
			= can[x+y+u] = can[x+z+u] = can[x+t+u] = can[y+z+u] = can[y+t+u] = can[z+t+u]
			= can[x+y+z+u] = can[x+y+t+u] = can[x+z+t+u] = can[y+z+t+u]
			= can[x+y+z+t+u] = false;
		can[u] = false;
	}
	return false;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i];
		sort(a+1, a+n+1);
		n = unique(a+1, a+n+1) - a - 1;
		s.clear();
		FOR(i,1,n) s.insert(a[i]);

		int res = 6;
		if (check1()) res = 1;
		else if (check2()) res = 2;
		else if (check3()) res = 3;
		else if (check4()) res = 4;
		else if (check5()) res = 5;
		cout << res << endl;
	}
	return 0;
}
