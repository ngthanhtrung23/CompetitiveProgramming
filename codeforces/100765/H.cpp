
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

#define EPS 1e-6
#ifndef M_PI
#define M_PI acos(-1.0)
#endif

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

    void read() { cin >> x >> y; }
    void print() { cout << x << ' ' << y << endl; }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

double angle(Point a, Point o, Point b) { // angle AOB
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

typedef vector< Point > Polygon;
bool in_polygon(const Polygon &P, Point pt) {
    if ((int)P.size() == 0) return false;
    double sum = 0;
    for (int i = 0; i < (int)P.size(); i++) {
        Point Pj = P[(i+1) % P.size()];
        // If allow on edge --> uncomment the following line
        // if (ccw(P[i], Pj, pt) == 0 && min(P[i], Pj) <= pt && pt <= max(P[i], Pj)) return true;
        if (ccw(pt, P[i], Pj) > 0)
            sum += angle(P[i], pt, Pj);
        else sum -= angle(P[i], pt, Pj);
    }
    return fabs(fabs(sum) - 2*M_PI) < EPS;
}

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow, id;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), g(n), q(n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap, int id) {
        Edge e1 = { a, b, cap, 0, id };
        Edge e2 = { b, a, 0, 0, id };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            REP(i,n) ptr[i] = 0;
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

    vector<int> getMinCut(int s, int t) {
        bfs();
        vector<int> res;
        REP(i,n) if (d[i] >= 0) {
            for(auto e_id : g[i]) {
                int j = e[e_id].b;
                if (d[j] < 0 && e[e_id].cap > 0) {
                    res.push_back(e[e_id].id);
                }
            }
        }
        return res;
    }

private:
    bool bfs() {
        int qh = 0, qt = 0;
        q[qt++] = s;
        REP(i,n) d[i] = -1;
        d[s] = 0;

        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            REP(i,g[v].size()) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

const int MN = 1011;
int nPoint, nSegment, nPolygon;
map< Point, int > id;
int poly_id[MN][MN], cost[MN][MN], edge_id[MN][MN];
vector<int> ke[MN];
Point a[MN], start, target;
Polygon p[MN];

void init() {
    nPoint = nPolygon = 0;
    id.clear();
    memset(poly_id, 0, sizeof poly_id);
    memset(cost, 0, sizeof cost);
    FOR(i,1,600) ke[i].clear();
}

int getId(const Point& p) {
    if (!id.count(p)) {
        ++nPoint;
        a[nPoint] = p;
        id[p] = nPoint;
    }
    return id[p];
}

double signed_area(Polygon p) {
    double area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}
double area(const Polygon &p) {
    return fabs(signed_area(p));
}

int findPolygon(Point X) {
    int best = -1;
    FOR(i,1,nPolygon)
    if (in_polygon(p[i], X)) {
        if (best < 0 || area(p[best]) > area(p[i]))
            best = i;
    }
    return best;
}

double ab_angle(Point P, Point c, Point Q) { // angle AOB
    double t = -atan2(P.y - c.y, P.x - c.x)
            + atan2(Q.y - c.y, Q.x - c.x);
    while (t < 0) t += 2*M_PI;
    return t;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nSegment) {
        FOR(i,1,nSegment) {
            Point u; u.read();
            Point v; v.read();

            int u_id = getId(u);
            int v_id = getId(v);

            cin >> cost[u_id][v_id];
            cost[v_id][u_id] = cost[u_id][v_id];

            edge_id[u_id][v_id] = edge_id[v_id][u_id] = i;

            ke[u_id].push_back(v_id);
            ke[v_id].push_back(u_id);
        }
        start.read(); target.read();
//        DEBUG(nPoint);
//        cout << "Points: " << endl;
//        FOR(i,1,nPoint) a[i].print();
//        cout << "Segments: " << endl;
//        FOR(u,1,nPoint) for(int v : ke[u]) cout << u << ' ' << v << endl;

        FOR(u,1,nPoint) {
            for(int v : ke[u]) if (!poly_id[u][v]) {
                try {
                    vector<int> cur;
                    cur.push_back(u);

                    int x = v;
                    while (x != u) {
                        cur.push_back(x);
                        int prev = cur[SZ(cur) - 2];

                        int best = -1;
                        for(int y : ke[x]) if (!poly_id[x][y] && y != prev) {
                            if (best == -1 || ab_angle(a[prev], a[x], a[y]) < ab_angle(a[prev], a[x], a[best]))
                                best = y;
                        }
                        if (best < 0) throw 1;

                        x = best;
                    }

//                    PR0(cur, cur.size());

                    ++nPolygon;
                    p[nPolygon].clear();
                    REP(i,SZ(cur)) {
                        int u = cur[ i ];
                        int v = cur[ (i+1) % SZ(cur) ];
                        poly_id[u][v] = nPolygon;

                        p[nPolygon].push_back(a[cur[i]]);
                    }
                } catch (...) {
                }
            }
        }

        int s = findPolygon(start);
        int t = findPolygon(target);

        MaxFlow flow(nPolygon+1);

        FOR(i,1,nPoint)
            FOR(j,i+1,nPoint)
                if (poly_id[i][j] || poly_id[j][i]) {
                    int u = poly_id[i][j];
                    int v = poly_id[j][i];

                    flow.addEdge(u, v, cost[i][j], edge_id[i][j]);
                    flow.addEdge(v, u, cost[i][j], edge_id[i][j]);
                }

        cout << flow.getMaxFlow(s, t) << endl;
        auto res = flow.getMinCut(s, t);
        cout << SZ(res) << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
}
