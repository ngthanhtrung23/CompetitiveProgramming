#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}
#define EPS 1e-12
const double PI = acos(-1.0);

bool equal(double x, double y) {
    if (fabs(x - y) < EPS) return true;
    return false;
}

const int MN = 100111;
int n;

struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line {
    double a, b, c;
    Line(double alpha) {
        a = sin(alpha);
        b = -cos(alpha);
        c = 0.0;
    }
    double f(Point A) {
        return (a*A.x + b*A.y);
    }
};


int bit[MN];
void initBIT() {
    memset(bit, 0, sizeof bit);
}
void update(int u, int val) {
    for(int x = u; x < MN; x += x & -x)
        bit[x] += val;
}
int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res += bit[x];
    return res;
}

pair<int,int> a[MN];
int cx[MN], cy[MN], sx, sy;

void RR() {
    FOR(i,1,n) cx[i] = a[i].first;
    sort(cx+1, cx+n+1);
    sx = unique(cx+1, cx+n+1) - cx - 1;
    FOR(i,1,n) a[i].first = lower_bound(cx+1, cx+sx+1, a[i].first) - cx;

    FOR(i,1,n) cy[i] = a[i].second;
    sort(cy+1, cy+n+1);
    sy = unique(cy+1, cy+n+1) - cy - 1;
    FOR(i,1,n) a[i].second = lower_bound(cy+1, cy+sy+1, a[i].second) - cy;
}

struct Elem {
    double f;
    int y;
    int id;
} e[MN];

bool operator < (const Elem&a, const Elem&b) {
    if (equal(a.f, b.f)) return a.y > b.y;
    return a.f < b.f;
}

int count(double mid) {
    Line l(mid);

    FOR(i,1,n) {
        e[i].f = -l.f(Point(cx[a[i].first], cy[a[i].second]));
        e[i].y = a[i].second;
        e[i].id = i;
    }
    sort(e+1, e+n+1);

    memset(bit, 0, sizeof bit);
    int res = 0;
    FOR(turn,1,n) {
        int i = e[turn].id;

        res += i - 1 - get(a[i].second - 1);
        update(a[i].second, +1);
    }
    return res;
}

double getK(int k) {
    double l = 0.0, r = PI;
    REP(turn,70) {
        double mid = (l + r) / 2.0;
        if (count(mid) >= k) {
            r = mid;
        }
        else l = mid;
    }
    return (l + r) / 2.0;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(18);
    while (GI(n) == 1) {
        FOR(i,1,n) {
            GI(a[i].first);
            GI(a[i].second);
        }
        RR();

        int N = n * (n - 1) / 2;

        if (N % 2 == 1) {
            double alpha = getK(N / 2 + 1);
            cout << alpha << endl;
        }
        else {
            double alpha1 = getK(N / 2);
            double alpha2 = getK(N / 2 + 1);
            cout << (alpha1 + alpha2) / (double) 2.0 << endl;
        }
    }
}
