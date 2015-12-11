
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

const int MN = 1011;

const double EPS = 1e-9;

int cmp(double a, double b) {
    if (fabs(a - b) < EPS) return 0;
    if (a < b) return -1;
    return 1;
}

struct D {
    double x;

    D() {}
    D(double x) : x(x) {}

    D operator + (const D& a) const { return D(x+a.x); }
    D operator - (const D& a) const { return D(x-a.x); }
    D operator * (const D& a) const { return D(x*a.x); }
    D operator / (const D& a) const { return D(x/a.x); }

    friend istream& operator >> (istream& cin, D& x) {
        cin >> x.x;
        return cin;
    }
    friend ostream& operator << (ostream& cout, D& x) {
        cout << x.x;
        return cout;
    }
};

D acos(D x) {
    return D(acos(x.x));
}

int cmp(D a, D b) {
    return cmp(a.x, b.x);
}

bool operator < (const D& a, const D& b) {
    return cmp(a, b) < 0;
}
bool operator != (const D& a, const D& b) {
    return cmp(a, b) != 0;
}
bool operator == (const D& a, const D& b) {
    return cmp(a, b) == 0;
}

struct Point {
    D x, y;

    Point() {}
    Point(D x, D y) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    D len() const {
        return D(hypot(x.x, y.x));
    }

    friend istream& operator >> (istream& cin, Point& a) {
        cin >> a.x >> a.y;
        return cin;
    }
    friend ostream& operator << (ostream& cout, Point& a) {
        cout << a.x << ' ' << a.y;
        return cout;
    }
};

bool operator < (const Point& a, const Point& b) {
    return a.len() < b.len();
}

vector<Point> a, b;
vector< pair<D,D> > fa, fb;
const D PI = D(acos(D(-1.0)));

D fixAngle(D alpha) {
    while (alpha < D(0.0)) alpha = alpha + D(2.0)*PI;
    while (D(2.0)*PI < alpha) alpha = alpha - D(2.0)*PI;
    return alpha;
}

D atan2(const D& x, const D& y) {
    return D(atan2(x.x, y.x));
}

D distance(D a, D b) {
    D res = a - b;
    return fixAngle(res);
}

int minmove(vector<pair<D,D> >& s) {
    int n = SZ(s);
    if (n == 0) return 0;
    if (n == 1) return 0;

    int x, y, i, j, u, v; // x is the smallest string before string y
    for (x = 0, y = 1; y < n; ++ y) {
        i = u = x;
        j = v = y;
        while (s[i] == s[j]) {
            ++ u; ++ v;
            if (++ i == n) i = 0;
            if (++ j == n) j = 0;
            if (i == x) break; // All strings are equal
        }
        if (s[i] <= s[j]) y = v;
        else {
            x = y;
            if (u > y) y = u;
        }
    }
    return x;
}

vector< pair<D,D> > f(vector<Point>& a, D& rot, int rev) {
    vector< pair<D, Point> > all;
    all.clear();
    FOR(i,1,SZ(a) - 1) {
        Point p = a[i] - a[0];
        D alpha = atan2(p.x, p.y);

        all.push_back(make_pair(alpha, p));
    }
    if (rev) {
        reverse(all.begin(), all.end());
    }
    sort(all.begin(), all.end());

    vector< pair<D,D> > res;
    if (all.empty()) {
        rot = D(0.0);
        return res;
    }

    REP(i,SZ(all)) {
        D alpha = distance(all[i].first, all[(i+1) % SZ(all)].first);
        res.push_back(make_pair(alpha, all[i].second.len()));
    }
    int x = minmove(res);
    rotate(res.begin(), res.begin()+x, res.end());

    rot = all[x].first;
//    DEBUG(rot);
    return res;
}

D MIN(const D& a, const D& b) {
    if (a < b) return a;
    return b;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);

    int n;
    while (cin >> n) {
        a.resize(n); b.resize(n);
        REP(i,n) cin >> a[i];
        REP(i,n) cin >> b[i];

        D rota;
        fa = f(a, rota, 0);
//        REP(i,SZ(fa)) cout << fa[i].first << ' ' << fa[i].second << endl; cout << endl;
        D res = 100;
        REP(turn,10) {
            random_shuffle(b.begin()+1, b.begin()+n);
            REP(i,n) {
                swap(b[i], b[0]);
                D rotb;
                fb = f(b, rotb, turn);
//                REP(i,SZ(fb)) cout << fb[i].first << ' ' << fb[i].second << endl; cout << endl;
                if (fa == fb) {
                    D angle = distance(rota, rotb);
                    res = MIN(res, angle);
                    res = MIN(res, D(2.0)*PI - angle);
                }
                swap(b[i], b[0]);
            }
        }
        cout << (fixed) << setprecision(9) << res << endl;
        break;
    }
}

