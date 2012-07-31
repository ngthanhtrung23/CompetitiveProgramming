//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

struct Point {
	long double x, y;
	Point() { x = y = 0; }
	Point(long double x, long double y) : x(x), y(y) {}

	Point operator - (Point a) { return Point(x-a.x, y-a.y); }

	long double len() { return sqrt(x*x + y*y); }
} A, B;

long double r1, r2;

int main() {
	cin >> A.x >> A.y >> r1;
	cin >> B.x >> B.y >> r2;
	long double r = (A - B).len();
	if (r >= r1 + r2) {
		r -= r1 + r2;
		if (r < 0) r = 0;
	}
	else if (r + r2 < r1) {
		r = r1 - r - r2;
	}
	else if (r + r1 < r2) {
		r = r2 - r - r1;
	}
	else {
		r = 0;
	}
	cout << (fixed) << setprecision(10) << r / 2 << endl;
    return 0;
}
