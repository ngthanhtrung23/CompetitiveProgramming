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

const double EPS = 1e-6;

#define ab(x) (((x) > 0) ? (x) : (-(x)))

struct Point {
	double x, y;

	Point(double x, double y) : x(x), y(y) {}
	Point() { x = y = 0; }

	Point operator + (Point a) { return Point(x+a.x, y+a.y); }
	Point operator - (Point a) { return Point(x-a.x, y-a.y); }

	void read() { cin >> x >> y; }

	double len() { return sqrt(x*x + y*y); }
} A, B, C;

struct Line {
	double a, b, c;
};

struct Circle : Point {
    long double r;
};

int intersection(Line l, Circle cir, Point &A, Point &B) {
    long double r, a, b, c;
    r = cir.r;
    a = l.a;
    b = l.b;
    c = l.c + l.a*cir.x + l.b*cir.y;

    long double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS) return 0;
    else if (ab(c*c - r*r*(a*a+b*b)) < EPS) {
        A = Point(x0, y0) + Point(cir.x, cir.y);
        return 1;
    }
    else {
        long double d = r*r - c*c/(a*a+b*b);
        long double mult = sqrt (d / (a*a+b*b));
        long double ax,ay,bx,by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        A = Point(ax, ay) + Point(cir.x, cir.y);
        B = Point(bx, by) + Point(cir.x, cir.y);
        return 2;
    }
}

double r;

void ans(Point X) {
	// DEBUG((A-X).len());
	// DEBUG((B-X).len());
	// DEBUG((C-X).len());
	puts("YES");
	printf("%.6lf %.6lf\n", X.x, X.y);
}

bool solve(Point A, Point B, Point C) {
	Point save = A;
	B = B - A;
	C = C - A;
	A = A - A;

	Circle OA;
	OA.x = A.x; OA.y = A.y; OA.r = r;

	Line l;
	l.a = -2*B.x;
	l.b = -2*B.y;
	l.c = B.x*B.x + B.y*B.y;

	Point X, Y;

	int t = intersection(l, OA, X, Y);

	if (t == 0) return false;

	if (t >= 1 && (C - X).len() <= r) {
		ans(X + save);
		return true;
	}
	if (t >= 2 && (C - Y).len() <= r) {
		ans(Y + save);
		return true;
	}
	return false;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> r) {
		A.read(); B.read(); C.read();
		if (solve(A, B, C)) continue;
		if (solve(B, C, A)) continue;
		if (solve(C, A, B)) continue;
		puts("NO");
	}
	return 0;
}
