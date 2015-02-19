
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

struct Point {
    ll x, y;

    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    Point operator * (ll k) const { return Point(x*k, y*k); }
    Point operator / (ll k) const { return Point(x/k, y/k); }
    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    void normalize() {
        if (x < 0) {
            x = -x; y = -y;
        }
        if (x == 0) y = 1;
        else if (y == 0) x = 1;
        else {
            ll g = __gcd(x, y);
            x /= g; y /= g;
        }
    }

    ll len() { return x*x + y*y; }
    void read() { scanf("%I64d%I64d", &x, &y); }
};

bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool operator == (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

struct Circle {
    Point O;
    ll r;

    void read() { O.read(); scanf("%I64d", &r); }
} circles[1511];

bool intersect(const Circle& a, const Circle& b) {
    ll dist = (a.O - b.O).len();
    if (dist > 4LL*a.r*a.r) return false;
    else return true;
}

struct Event {
    Point dir, x;
    int typ;
    ll offset;
} events[3000111];

bool operator < (const Event& a, const Event& b) {
    if (a.dir == b.dir) {
        if (a.offset != b.offset) return a.offset < b.offset;
        else if (a.x == b.x) return a.typ < b.typ;
        else return a.x < b.x;
    }
    else return a.dir < b.dir;
}

int main() {
    int nLine, nCircle, nEvent;
    while (scanf("%d%d", &nLine, &nCircle) == 2) {
        nEvent = 0;
        FOR(i,1,nLine) {
            Point A, B; A.read(); B.read();
            A = A * 2;
            B = B * 2;

            Point dir = B - A;
            swap(dir.x, dir.y);
            dir.y = -dir.y;

            dir.normalize();
            if (B < A) swap(A, B);

            ll offset = - (dir.x*A.x + dir.y*A.y);

            ++nEvent;
            events[nEvent].dir = dir; events[nEvent].x = A; events[nEvent].typ = 1;
            events[nEvent].offset = offset;

            ++nEvent;
            events[nEvent].dir = dir; events[nEvent].x = B; events[nEvent].typ = 3;
            events[nEvent].offset = offset;
        }
//        cout << "DONE LINE" << endl;
        FOR(i,1,nCircle) {
            circles[i].read();
            circles[i].O = circles[i].O * 2;
            circles[i].r *= 2;
        }

        FOR(i,1,nCircle) FOR(j,i+1,nCircle)
        if (!intersect(circles[i], circles[j]) && circles[i].r == circles[j].r) {
            Point dir = circles[i].O - circles[j].O;
            dir.normalize();

            Point mid = (circles[i].O + circles[j].O) / 2;

            ++nEvent;
            events[nEvent].dir = dir;
            events[nEvent].x = mid;
            events[nEvent].typ = 2;
            events[nEvent].offset = - (dir.x*mid.x + dir.y*mid.y);
        }
//        cout << "DONE CIRCLE" << endl;

        sort(events+1, events+nEvent+1);
        ll res = 0;
        int cur = 0;
        events[0].dir = events[1].dir * 2;
        FOR(i,1,nEvent) {
            if (!(events[i].dir == events[i-1].dir) || events[i].offset != events[i-1].offset)
                cur = 0;

            switch (events[i].typ) {
                case 1:
                    ++cur;
                    break;
                case 2:
                    res += cur;
                    break;
                case 3:
                    --cur;
                    break;
            }
        }
        printf("%I64d\n", res);
    }
    return 0;
}

