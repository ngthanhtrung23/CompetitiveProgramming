#include <bits/stdc++.h>
#define int long long
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

const double EPS = 1e-9;

struct Point {
    int x, y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
    int operator * (Point a) {
        return x*a.x + y*a.y;
    }
    int operator % (const Point& a) {
        return x*a.y - y*a.x;
    }

    double norm() {
        return x * x + y * y;
    }
    double len() {
        return sqrt(norm());
    }

    void read() {
        scanf("%lld%lld", &x, &y);
    }
} A[5], B[5];

bool operator == (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

int ccw(Point A, Point B, Point C) {
    int t = (B - A) % (C - A);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

const double PI = acos((double) -1.0);
double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    double res = acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
    while (res < -EPS) res += 2 * PI;

    while (res >= 2*PI) res -= 2 * PI;
    return res;
}

bool order(Point A, Point B, Point C) {
    return min(A.x, C.x) <= B.x && B.x <= max(A.x, C.x)
        && min(A.y, C.y) <= B.y && B.y <= max(A.y, C.y);
}

bool good(Point A, Point B, Point C) {
    if (ccw(A, B, C)) return false;
    if (!order(A, B, C)) return false;

    double x = (B - A).len();
    double y = (C - B).len();

    if (x * 4 < y - EPS) return false;
    if (y * 4 < x - EPS) return false;

    return true;
}

bool check() {
    int t[5];
    FOR(i,1,3) t[i] = i;

    do {
        REP(r1,2) {
            REP(r2,2) {
                REP(r3,2) {
                    if (A[t[1]] == A[t[2]]
                            && ccw(A[t[1]], B[t[1]], B[t[2]]) // must not collinear
                            && angle(B[t[1]], A[t[1]], B[t[2]]) < PI / 2.0 + EPS
                            && good(A[t[1]], A[t[3]], B[t[1]])
                            && good(A[t[2]], B[t[3]], B[t[2]]))
                    {
                        return true;
                    }
                    swap(A[3], B[3]);
                }
                swap(A[2], B[2]);
            }
            swap(A[1], B[1]);
        }
    } while (next_permutation(t+1, t+4));
    return false;
}

#undef int
int main() {
#define int long long
    int ntest; scanf("%lld", &ntest);
    while (ntest--) {
        FOR(i,1,3) {
            A[i].read();
            B[i].read();
        }

        puts(check() ? "YES" : "NO");
    }
}
