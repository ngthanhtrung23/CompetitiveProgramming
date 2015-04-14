
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const double EPS = 1e-12;

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    int id;
    Point(double x = 0.0, double y = 0.0, int id = 0) : x(x), y(y), id(id) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (double k) { return Point(x*k, y*k); }
    Point operator / (double k) { return Point(x/k, y/k); }

    double operator * (Point a) { return x*a.x + y*a.y; } // dot product
    double operator % (Point a) { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point conj() { return Point(x, -y); }
    double norm() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};
double cross(Point p, Point q) { return p.x*q.y-p.y*q.x; }
double area2(Point a, Point b, Point c) { return cross(a,b) + cross(b,c) + cross(c,a);}

int ccw(Point a, Point b, Point c) {
    double t = cross(b-a, c-a);
    if (fabs(t) < EPS) return 0;
    else if (t < 0) return -1;
    else return 1;
}

#ifdef REMOVE_REDUNDANT
bool between(const Point &a, const Point &b, const Point &c) {
    return (fabs(area2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

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
    
#ifdef REMOVE_REDUNDANT
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
#endif
}

int bit[10111];
const int MN = 200111;
bool can[MN];
#define _(X) ((X) & (-(X)))
void update(int u, int val) {
    while (u <= 10000) {
        bit[u] = max(bit[u], val);
        u += _(u);
    }
}
int get(int u) {
    int res = 0;
    while (u > 0) {
        res = max(res, bit[u]);
        u -= _(u);
    }
    return res;
}

pair<int,int> input[MN];
int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d", &n) == 1) {
        vector<Point> a;
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            int x, y;
            scanf("%d%d", &x, &y);
            a.push_back(Point(1.0/x, 1.0/y, i));
            
            input[i] = make_pair(10001-x, y);
            update(input[i].first, input[i].second);
        }

        FOR(i,1,n) {
            if (get(input[i].first-1) >= input[i].second) can[i] = false;
            else if (get(input[i].first) > input[i].second) can[i] = false;
            else can[i] = true;
        }
        ConvexHull(a);
        set<int> res;
        int sz = a.size();

//        cout << "Convex: " << endl;
//        for(auto p : a) {
//            cout << p.x << ' ' << p.y << endl;
//        }

        Point O(0, 0, 0);
        REP(i,sz) {
            Point y = a[i];
            Point x = a[(i-1+sz)%sz];
            Point xx = a[(i-2+sz+sz)%sz];
            Point z = a[(i+1) % sz];
            Point zz = a[(i+2) % sz];

            if (ccw(x, y, z) * ccw(x, y, O) <= 0
                    && ccw(x, y, xx) * ccw(x, y, O) <= 0)
                res.insert(a[i].id);

            if (ccw(y, z, x) * ccw(y, z, O) <= 0
                    && ccw(y, z, zz) * ccw(y, z, O) <= 0)
                res.insert(a[i].id);
        }
        set<pair<int,int> > all;
        for(int x : res) if (can[x]) all.insert(input[x]);

        FOR(i,1,n) if (all.count(input[i])) cout << i << ' '; cout << endl;
    }
    return 0;
}
