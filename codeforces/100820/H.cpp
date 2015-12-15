
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
using namespace std;

const int MN = 200111;

int n, S;
string name[MN];
char tmp[100111];
struct Point {
    double x, y;
    int id;

    Point() {}
    Point(double x, double y, int id) : x(x), y(y), id(id) {}
} a[MN];
int x[MN], y[MN];

void go(vector<Point> all, double xmin, double ymin, double xmax, double ymax) {
//    cout << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << endl;
//    cout << "Sort: "; for(auto p : all) cout << p.id << ' '; cout << endl;
    if (all.empty()) return ;
    if (SZ(all) == 1) {
        puts(name[all[0].id].c_str());
        return ;
    }
    double xmid = (xmin + xmax) / 2.0;
    double ymid = (ymin + ymax) / 2.0;

    vector<Point> f1, f2, f3, f4;
    for(auto p : all) {
        if (p.x < xmid && p.y < ymid) {
            f1.push_back(Point(p.y, p.x, p.id));
        }
        else if (p.x < xmid) {
            f2.push_back(Point(p.x, p.y - ymid, p.id));
        }
        else if (p.y > ymid) {
            f3.push_back(Point(p.x - xmid, p.y - ymid, p.id));
        }
        else {
            double x = xmax - p.x;
            double y = ymid - p.y;
            f4.push_back(Point(y, x, p.id));
        }
    }
    go(f1, xmin, ymin, xmid, ymid);
    go(f2, xmin, ymin, xmid, ymid);
    go(f3, xmin, ymin, xmid, ymid);
    go(f4, xmin, ymin, xmid, ymid);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d\n", &n, &S) == 2) {
        FOR(i,1,n) {
            scanf("%d %d %s\n", &x[i], &y[i], &tmp[0]);
            name[i] = string(tmp);
        }
        vector<Point> all;
        FOR(i,1,n) all.push_back(Point(x[i], y[i], i));

        go(all, 0, 0, S, S);
    }
}
