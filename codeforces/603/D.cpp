#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define sqr(x) ((x) * (x))
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

const int MN = 2011;
const double EPS = 1e-12;

int cmp(double x, double y) {
    if (fabs(x - y) < EPS) return 0;
    if (x < y) return -1;
    return 1;
}

struct D { // replacement for double
    double x;

    D() {}
    D(double x) : x(x) {}

    D operator + (const D& a) const { return D(x+a.x); }
    D operator - (const D& a) const { return D(x-a.x); }
    D operator * (const D& a) const { return D(x*a.x); }
    D operator / (const D& a) const { return D(x/a.x); }

    D operator - () const { return D(-x); }

    D& operator += (const D& a) { return *this = *this + a; }
    D& operator -= (const D& a) { return *this = *this - a; }
    D& operator *= (const D& a) { return *this = *this * a; }
    D& operator /= (const D& a) { return *this = *this / a; }

    bool operator == (const D& a) const { return cmp(x, a.x) == 0; }
    bool operator <= (const D& a) const { return cmp(x, a.x) <= 0; }
    bool operator >= (const D& a) const { return cmp(x, a.x) >= 0; }
    bool operator <  (const D& a) const { return cmp(x, a.x) <  0; }
    bool operator >  (const D& a) const { return cmp(x, a.x) >  0; }
    bool operator != (const D& a) const { return cmp(x, a.x) != 0; }

    int sign() {
        int t = cmp(x, 0);
        if (t == 0) return 0;
        if (t < 0) return -1;
        return 1;
    }

    friend istream& operator >> (istream& cin, D& x) {
        cin >> x.x;
        return cin;
    }
    friend ostream& operator << (ostream& cout, D& x) {
        cout << x.x;
        return cout;
    }
};


struct Fraction {
	ll x, y;

	Fraction() { x = 0, y = 1; }
	Fraction(ll _x, ll _y) {
		ll g = __gcd(llabs(_x), llabs(_y));
		x = _x / g;
		y = _y / g;

		if (y < 0) {
			x = -x;
			y = -y;
		}
	}

	Fraction operator + (const Fraction& a) {
		return Fraction(x*a.y + y*a.x, y*a.y);
	}
	Fraction operator - (const Fraction& a) {
		return Fraction(x*a.y - y*a.x, y*a.y);
	}
	Fraction inverse() {
		return Fraction(y, x);
	}
	Fraction operator * (const Fraction& a) {
		return Fraction(x*a.x, y*a.y);
	}

	D toD() {
		return D(x) / D(y);
	}
};

bool operator == (const Fraction& a, const Fraction& b) {
	if (a.x / a.y != b.x / b.y) return false;
	return a.x*b.y == a.y*b.x;
}
bool operator != (const Fraction& a, const Fraction& b) {
	return a.x*b.y != a.y*b.x;
}
bool operator < (const Fraction& a, const Fraction& b) {
	return a.x*b.y < a.y*b.x;
}

struct Point {
	Fraction x, y;

	Point() {}
	Point(Fraction x, Fraction y) : x(x), y(y) {}

	Point operator - (const Point& a) {
		return Point(x-a.x, y-a.y);
	}
};

bool operator == (const Point& a, const Point& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator < (const Point& a, const Point& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

int n;
struct Line {
	ll a, b, c;

	void read() {
		cin >> a >> b >> c;
	}
} lines[MN];
Point a[MN];

ll C2(ll x) {
	return x * (x-1LL) / 2;
}

int main() {
	while (cin >> n) {
		FOR(i,1,n) lines[i].read();
		FOR(i,1,n) {
			ll t = sqr(lines[i].a) + sqr(lines[i].b);
			a[i].x = Fraction(-lines[i].a * lines[i].c, t);
			a[i].y = Fraction(-lines[i].b * lines[i].c, t);
		}
		ll res = 0;
		Fraction zero(0, 1);
		Fraction one(1, 1);
		FOR(i,1,n) {
			int same = 0;
			map< pair<D, D>, ll > cnt;
			FOR(j,i+1,n) {
				if (a[i] == a[j]) {
					++same;
				}
				else {
					D dx = a[j].x.toD() - a[i].x.toD();
					D dy = a[j].y.toD() - a[i].y.toD();

					if (dx == 0) dy = 1;
					else if (dy == 0) dx = 1;
					else {
						D len = hypot(dx.x, dy.x);
						dx /= len;
						dy /= len;

						if (dx < 0) dx = -dx, dy = -dy;
					}
					cnt[ make_pair(dx, dy) ] += 1;
				}
			}
			res += C2(same);
			for(auto p : cnt) {
				res += C2(p.second);
				res += same * p.second;
			}
		}
		cout << res << endl;
	}
}
