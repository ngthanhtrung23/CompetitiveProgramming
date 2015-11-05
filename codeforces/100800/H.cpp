
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
#define double long double
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 200111;

struct Point {
    ll x, y;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    ll operator * (const Point& a) const {
        return x*a.x + y*a.y;
    }
    ll norm() {
        return x*x + y*y;
    }

    void read() {
        int t;
        scanf("%d", &t); x = t;
        scanf("%d", &t); y = t;
    }
} a[MN];

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    ll t = b.x*c.y - b.y*c.x;
    if (t == 0) return 0;
    else if (t > 0) return 1;
    else return -1;
}

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

int st[MN], top;
double l[MN], r[MN];
double PI = acos(-1.0);

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
//    DEBUG(ccw(Point(0, 2), Point(1, 1), Point(2, 1)));
//    DEBUG(ccw(Point(0, 2), Point(-1, 1), Point(-2, 1)));

    int n;
    while (scanf("%d", &n) == 1) {
        top = 0;
        FOR(i,1,n) a[i].read();

        top = 0;
        FOR(i,1,n) {
            while (top > 0 && a[i].y >= a[ st[top] ].y) --top;
            while (top > 1 && ccw(a[ st[top-1] ], a[st[top]], a[i]) >= 0) --top;

            if (top == 0) l[i] = PI / 2.0;
            else {
                l[i] = angle(Point(a[i].x, a[i].y + 1), a[i], a[st[top]]);
            }
            st[++top] = i;
        }
        top = 0;
        FORD(i,n,1) {
            while (top > 0 && a[i].y >= a[st[top]].y) --top;
            while (top > 1 && ccw(a[ st[top-1] ], a[st[top]], a[i]) <= 0) --top;

            if (top == 0) r[i] = PI / 2.0;
            else {
                r[i] = angle(Point(a[i].x, a[i].y + 1), a[i], a[st[top]]);
            }
            st[++top] = i;
        }
        FOR(i,1,n) {
            cout << (l[i] + r[i]) / PI * 12.0 << endl;
        }
    }
}

