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

struct Point {
	long long x, y;

	Point() {}
	Point(long long x, long long y) : x(x), y(y) {}

	Point operator + (Point a) { return Point(x+a.x, y+a.y); }
	Point operator - (Point a) { return Point(x-a.x, y-a.y); }
} a[111][10111];

bool operator < (const Point &a, const Point &b) {
	if (a.x != b.x) return a.x < b.x;
	else if (a.y != b.y) return a.y < b.y;
	else return 0;
}
int m, n;

void transform(int i) {
	FORD(j,m,2) a[i][j] = a[i][j] - a[i][j-1];
}

bool check(int i) {
	if (m == 1) return true;

	bool foundR = false;
	long long r_a, r_b;
	FOR(j,2,m) if (a[0][j].x) {
		if (a[i][j].x == 0) return false;
		r_a = a[0][j].x;
		r_b = a[i][j].x;
		foundR = true;
		break;
	}
	FOR(j,2,m) if (a[0][j].y) {
		if (a[i][j].y == 0) return false;
		r_a = a[0][j].y;
		r_b = a[i][j].y;
		foundR = true;
		break;
	}

	if (!foundR) {
		FOR(j,2,m) {
			if (a[i][j].x) return false;
			if (a[i][j].y) return false;
		}
	}
	if (r_a * r_b < 0) return false;

	FOR(j,2,m) {
		if (a[i][j].x * r_a != a[0][j].x * r_b) return false;
		if (a[i][j].y * r_a != a[0][j].y * r_b) return false;
	}
	return true;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n >> m) {
		FOR(i,0,n) {
			FOR(j,1,m) cin >> a[i][j].x >> a[i][j].y;

			sort(a[i]+1, a[i]+m+1);
			// FOR(j,1,m) cout << a[i][j].x << ' ' << a[i][j].y << "   "; cout << endl;
			transform(i);

			// FOR(j,2,m) cout << a[i][j].x << ' ' << a[i][j].y << "   "; cout << endl;
		}

		FOR(i,1,n) {
			if (check(i)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
