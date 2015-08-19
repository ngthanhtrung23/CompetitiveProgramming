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

const int MN = 311;
const double PI = acos(-1.0);

double r[MN];

#define EPS 1e-6
inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

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
} a[MN];
int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

typedef vector< Point > Polygon;
double angle(Point a, Point o, Point b) { // angle AOB
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}
bool in_polygon(const Polygon &P, Point pt) {
    if ((int)P.size() == 0) return false;
    double sum = 0;
    for (int i = 0; i < (int)P.size(); i++) {
        Point Pj = P[(i+1) % P.size()];
        if (ccw(pt, P[i], Pj) > 0)
            sum += angle(P[i], pt, Pj);
        else sum -= angle(P[i], pt, Pj);
    }
    return fabs(fabs(sum) - 2*PI) < EPS;
}
struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int n, m;
pair<int,int> edges[MN * MN];
vector<int> ke[MN];
int good[MN * MN];
int visited[MN];
bool stuck;
Point King;

void go(int start, int target) {
    memset(visited, 0, sizeof visited);
    queue<int> qu; qu.push(start);
    visited[start] = start;
    
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for(int v : ke[u]) {
            if (visited[v]) continue;

            visited[v] = u;
            qu.push(v);
        }
    }

    if (visited[target]) {
        int x = target;
        vector<int> res;
        while (x != start) {
            res.push_back(x);
            x = visited[x];
        }
        res.push_back(start);
//        PR0(res, res.size());

        Polygon P;
        for(auto id : res) P.push_back(a[id]);

        if (in_polygon(P, King)) {
            stuck = true;
//            cout << "HERE" << endl;
        }
    }
}

int main() {
    freopen("out.in", "r", stdin);
    freopen("out.out", "w", stdout);
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        memset(good, 0, sizeof good);
//        DEBUG(n);
        FOR(i,1,n) cin >> a[i].x >> a[i].y >> r[i];
        Point P; cin >> P.x >> P.y; double R; cin >> R;
        King = P;

        FOR(i,1,n) r[i] += R;

        DSU dsu; dsu.init(n);
        int cnt = 0;
        FOR(i,1,n) FOR(j,i+1,n) {
            if ((a[i] - a[j]).len() < r[i] + r[j] - 1e-6) {
                edges[++cnt] = make_pair(i, j);
            }
        }
        FOR(i,1,cnt) {
            int u = edges[i].first, v = edges[i].second;
            if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

            dsu.merge(u, v);
            ke[u].push_back(v);
            ke[v].push_back(u);
            good[i] = 1;
        }
        stuck = false;
        FOR(i,1,cnt) {
            if (good[i]) continue;

            go(edges[i].first, edges[i].second);
            if (stuck) break;
        }
        cout << (stuck ? "NO" : "YES") << endl;
    }
}