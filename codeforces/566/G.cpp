
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

struct Point {
    ll x, y;

    Point(ll x = 0, ll y = 0) : x(x), y(y) {};

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (ll k) { return Point(x*k, y*k); }

    ll operator * (Point a) { return x*a.x + y*a.y; } // dot product
    ll operator % (Point a) { return x*a.y - y*a.x; } // cross product
};

bool operator < (const Point& a, const Point& b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}
bool operator == (const Point& a, const Point& b) {
    return make_pair(a.y, a.x) == make_pair(b.y, b.x);
}

typedef vector< Point > Polygon;

#define REMOVE_REDUNDANT

ll area2(Point a, Point b, Point c) { return a%b + b%c + c%a; }
#ifdef REMOVE_REDUNDANT
bool between(const Point &a, const Point &b, const Point &c) {
    return llabs(area2(a, b, c)) == 0 && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0;
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

#define Det(a,b,c) ((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))
bool in_convex(vector<Point>& l, Point p){
    int a = 1, b = l.size()-1, c;
    if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
    // Allow on edge --> if (Det... > 0 || Det ... < 0)
    if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
    while(abs(a-b) > 1) {
        c = (a+b)/2;
        if (Det(l[0], l[c], p) > 0) b = c; else a = c;
    }
    // Alow on edge --> return Det... <= 0
    return Det(l[a], l[b], p) < 0;
}

int main() {
    ios :: sync_with_stdio(false);
    int nMax, nMin, x, y;
    while (cin >> nMax >> nMin) {
        cin >> x >> y;
        Polygon a;
        a.push_back(Point(0, 0));

        Polygon b;
        FOR(i,1,nMax) {
            int x, y; cin >> x >> y;
            b.push_back(Point(x, y));
        }

        int max_x = 0, max_y = 0;
        FOR(i,1,nMin) {
            int x, y; cin >> x >> y;
            a.push_back(Point(x, y));

            max_x = max(max_x, x);
            max_y = max(max_y, y);
        }
        a.push_back(Point(max_x, 0));
        a.push_back(Point(0, max_y));
        ConvexHull(a);

//        for(auto p : a) cout << p.x << ' ' << p.y << endl;
//        cout << endl;

        bool ok = true;
        for(auto p : b) if (!in_convex(a, p)) {
            ok = false;
            break;
        }
        cout << (ok ? "Min" : "Max") << endl;
    }
}

