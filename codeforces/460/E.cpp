#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

inline int cmp(int a, int b) {
    return (a < b) ? -1 : ((a > b) ? 1 : 0);
}

struct Point {
    int x, y;
    Point(int x = 0.0, int y = 0.0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (int k) { return Point(x*k, y*k); }
    Point operator / (int k) { return Point(x/k, y/k); }

    int operator * (Point a) { return x*a.x + y*a.y; } // dot product
    int operator % (Point a) { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    int norm() { return x*x + y*y; }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

typedef vector< Point > Polygon;
struct comp_hull {
    Point pivot;
    bool operator() (Point q,Point w) {
        Point Q = q - pivot, W = w - pivot;
        double R = Q % W;
        if (cmp(R,0)) return R < 0;
        return cmp(Q*Q,W*W) < 0;
    }
};
Polygon convex_hull(Polygon p) { // minimum vertices
    int j = 0, k, n = p.size();
    Polygon r(n);
    if (!n) return r;
    comp_hull comp;
    comp.pivot = *min_element(p.begin(),p.end());
    sort(p.begin(),p.end(),comp);
    for(int i = 0; i < n; ++i) {
        while (j > 1 && ccw(r[j-1],r[j-2],p[i]) <= 0) j--;
        r[j++] = p[i];
    }
    r.resize(j);
    if (r.size() >= 2 && r.back() == r.front()) r.pop_back();
    return r;
}
int n, r;
Polygon a;
int res;
Polygon save;

void attempt(int u, vector<Point> &cur, int last, int sum) {
    if (u > n) {
        if (sum > res) {
            res = sum;
            save = cur;
        }
        return ;
    }
    for(int x = last; x < a.size(); ++x) {
        int newSum = sum;
        for(auto p : cur) {
            newSum += (p - a[x]).norm();
        }
        cur.push_back(a[x]);
        attempt(u+1, cur, x, newSum);
        cur.pop_back();
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> r) {
        if (n % 2 == 0) {
            FOR(i,1,n/2) {
                a.push_back(Point(r, 0));
                a.push_back(Point(-r, 0));
            }
            int sum = 0;
            REP(i,a.size()) FOR(j,i+1,a.size()-1)
                sum += (a[i] - a[j]).norm();
            cout << sum << endl;
            for(auto p : a)
                cout << p.x << ' ' << p.y << endl;
            continue;
        }
        a.clear();
        FOR(x,-r,r) FOR(y,-r,r)
            if (Point(x, y).norm() <= r*r) {
                a.push_back(Point(x, y));
            }
        a = convex_hull(a);
//        DEBUG(a.size());

        res = 0;
        save.clear();
        vector<Point> cur;
        attempt(1, cur, 0, 0);
        cout << res << endl;
        for(auto p : save) {
            cout << p.x << ' ' << p.y << endl;
        }
    }
    return 0;
}

