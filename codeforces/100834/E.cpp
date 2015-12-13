
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

const int MN = 111;
const double EPS = 1e-9;

int n;

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
} O(0.0), PI(acos((double) -1.0));

int cmp(const D& a, const D& b) {
	return cmp(a.x, b.x);
}

#define Func(op) D op(const D& a) { return D(op(a.x)); }
Func(sin); Func(cos); Func(tan); Func(asin); Func(acos); Func(atan); Func(sqrt); Func(fabs);
#undef Func

struct Point {
	D x, y;
	Point() {}
	Point(D x, D y) : x(x), y(y) {}
	
	Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
	Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
	Point operator * (const D& k) const { return Point(x*k, y*k); }
	Point operator / (const D& k) const { return Point(x/k, y/k); }

	D operator * (const Point& a) const { return x*a.x + y*a.y; }
	D operator % (const Point& a) const { return x*a.y - y*a.x; }

	D norm() { return x*x + y*y; }
	D len() { return hypot(x.x, y.x); }

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point normalize(D l) {
        return Point(x, y) * l / len();
    }
};
struct Line {
    D a, b, c;
    Point A, B;

    Line(D a, D b, D c) : a(a), b(b), c(c) {}

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = D(0) - (a * A.x + b * A.y);
    }

	D f(const Point &p) {
		return a*p.x + b*p.y + c;
	}

	D dist(Point p) {
		return fabs(a*p.x + b*p.y + c) / sqrt(a*a + b*b);
	}
};
int ccw(Point a, Point b, Point c) {
	D t = (b - a) % (c - a);
	if (t == O) return 0;
	if (t < O) return -1;
	return 1;
}

bool areParallel(Line l1, Line l2) {
    return l1.a*l2.b == l1.b*l2.a;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1 ,l2) && l1.c*l2.a == l2.c*l1.a
            && l1.c*l2.b == l1.b*l2.c;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    D dx = l1.b*l2.c - l2.b*l1.c;
    D dy = l1.c*l2.a - l2.c*l1.a;
    D d    = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

struct Circle : Point {
	D r;
} a[MN];

// Find common tangents to 2 circles
// Helper method
void tangents(Point c, D r1, D r2, vector<Line> & ans) {
    D r = r2 - r1;
    D z = sqr(c.x) + sqr(c.y);
    D d = z - sqr(r);
    if (d < -EPS)    return;
    d = sqrt(fabs(d));
    Line l((c.x * r + c.y * d) / z,
            (c.y * r - c.x * d) / z,
            r1);
    ans.push_back(l);
}
// Actual method: returns vector containing all common tangents
vector<Line> tangents(Circle a, Circle b) {
    vector<Line> ans; ans.clear();
    for (int i=-1; i<=1; i+=2)
        for (int j=-1; j<=1; j+=2)
            tangents(b-a, a.r*i, b.r*j, ans);
    for(int i = 0; i < ans.size(); ++i)
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;

    vector<Line> ret;
    for(int i = 0; i < (int) ans.size(); ++i) {
        bool ok = true;
        for(int j = 0; j < i; ++j)
            if (areSame(ret[j], ans[i])) {
                ok = false;
                break;
            }
        if (ok) ret.push_back(ans[i]);
    }
    return ret;
}

bool intersect(Circle c, Line l) {
	return l.dist(c) < c.r;
}

vector<Point> intersection(Line l, Circle cir) {
    D r = cir.r, a = l.a, b = l.b, c = l.c + l.a*cir.x + l.b*cir.y;
    vector<Point> res;

    D x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)) return res;
    else if (c*c == r*r*(a*a+b*b)) {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    }
    else {
        D d = r*r - c*c/(a*a+b*b);
        D mult = sqrt (d / (a*a+b*b));
        D ax,ay,bx,by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
        res.push_back(Point(bx, by) + Point(cir.x, cir.y));
        return res;
    }
}

bool check(Line l) {
	FOR(i,1,n) if (intersect(a[i], l)) return false;

	int t = l.f(a[1]).sign();

	FOR(i,2,n) if (l.f(a[i]).sign() != t) return false;
	return true;
}

typedef vector< Point > Polygon;

D area2(Point a, Point b, Point c) { return a%b + b%c + c%a; }
bool between(const Point &a, const Point &b, const Point &c) {
    return (fabs(area2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
}
D signed_area(Polygon p) {
    D area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}
D area(const Polygon &p) {
    return fabs(signed_area(p));
}
D angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i].x >> a[i].y >> a[i].r;

		Polygon all;
		FOR(i,1,n) FOR(j,i+1,n) {
			auto p = tangents(a[i], a[j]);
			for(auto l : p) {
				if (check(l)) {
					auto cur = intersection(l, a[i]);
					for(auto p : cur) all.push_back(p); 
					cur = intersection(l, a[j]);
					for(auto p : cur) all.push_back(p);
				}
			}
		}

		ConvexHull(all);
//		for(auto p : all) cout << '(' << p.x << ',' << p.y << ')' << "    "; cout << endl;

		D totalArea = area(all);
		D totalLen = D(0.0);

		REP(i,SZ(all)) {
			int j = (i + 1) % SZ(all);
			int k = (j + 1) % SZ(all);
			Line l(all[i], all[j]);

			int t = l.f(all[k]).sign();

			bool good = true;
			FOR(cid,1,n) if (l.dist(a[cid]) < a[cid].r) {
				good = false;

				D alpha = angle(all[i], a[cid], all[j]);

				if (ccw(all[i], a[cid], all[j]) != 0) {
					Point mid = (all[i] + all[j]) / 2.0;
					Point u = (mid - a[cid]).normalize(a[cid].r) + a[cid];

					if (l.f(u).sign() == t) {
						alpha = D(2.0)*PI - alpha;
						totalArea += alpha / D(2.0) * sqr(a[cid].r);
						totalArea += fabs(area2(a[cid], all[i], all[j]) / D(2.0));
					}
					else {
						totalArea += alpha / D(2.0) * sqr(a[cid].r);
						totalArea -= fabs(area2(a[cid], all[i], all[j]) / D(2.0));
					}
				}
				else {
					totalArea += PI * a[cid].r * a[cid].r / D(2.0);
				}

				totalLen += alpha * a[cid].r;
			}
			if (good) totalLen += (all[i] - all[j]).len();
		}

		cout << totalLen << ' ' << totalArea << endl;
	}
}
