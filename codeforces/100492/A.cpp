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
using namespace std;

int RI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 600111;

struct Point {
    int x, y;
    Point() { x = y = 0; }
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    Point operator + (const Point& a) const {
        return Point(x+a.x, y+a.y);
    }
    int operator % (const Point& a) const {
        return x*a.y - y*a.x;
    }

    void read() {
        RI(x); RI(y);
    }

    int sqlen() const { return x*x + y*y; }
};
bool operator == (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator != (const Point& a, const Point& b) {
    return a.x != b.x || a.y != b.y;
}
int ccw(const Point &a, const Point &b, const Point &c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

int n;
Point a[MN];

int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));

bool cmp(const Point& u, const Point& v) {
    int t = ccw(a[1], u, v);
    if (t == RE_TRAI) return true;
    if (t == RE_PHAI) return false;
    return (u - a[1]).sqlen() < (v - a[1]).sqlen();
}

void answer(int a, int b) {
    int g = __gcd(a, b);
    cout << (a/g) << '/' << (b/g) << endl;
}

bool sameLine() {
    FOR(i,3,n) if (ccw(a[1], a[2], a[i])) return 0;
    return 1;
}

int st[MN], top;
int st2[MN], top2;

#undef int
int main() {
#define int long long
    freopen("average.in", "r", stdin);
    freopen("average.out", "w", stdout);
    while (RI(n) == 1) {
        FOR(i,1,n) a[i].read();

        FOR(i,2,n) if (a[i].y < a[1].y || (a[i].y == a[1].y && a[i].x < a[1].x)) swap(a[1], a[i]);
        sort(a+2, a+n+1, cmp);

        if (sameLine()) {
            answer(2, 1);
            continue;
        }

        int last = n;
        while (last > 2 && ccw(a[1], a[last], a[last-1]) == 0) --last;
        reverse(a+last, a+n+1);

        FOR(i,n+1,n+n+n) a[i] = a[i-n];

        st[1] = 1;
        st[2] = 2;
        top = 2;
        FOR(i,3,n) {
            while (top >= 2 && ccw(a[st[top-1]], a[st[top]], a[i]) != RE_TRAI) {
                --top;
            }
            st[++top] = i;
        }
        while (top >= 2 && ccw(a[st[top-1]], a[st[top]], a[1]) != RE_TRAI) --top;

        assert(top >= 3);

        int res = top * (n - top);
        st[top+2] = st[2];
        st[top+1] = st[1];
        st[0] = st[top];

        FOR(turn,2,top) {
            int u = st[turn-1] + 1;
            int v = st[turn+1] - 1;
            if (v < u) v += n;

            top2 = 2;
            st2[1] = st[turn-2];
            st2[2] = st[turn-1];
            FOR(i,u,v) if (a[i] != a[st[turn]]) {
                while (ccw(a[st2[top2-1]], a[st2[top2]], a[i]) != RE_TRAI) --top2;
                assert(top2 >= 2);
                st2[++top2] = i;
            }
            while (top2 >= 3 && ccw(a[st2[top2-1]], a[st2[top2]], a[st[turn+1]]) != RE_TRAI)
                --top2;

            int cur = top - 1 + top2 - 2;
            if (cur < 2) cur = 2;

//            cout << "REM " << a[st[turn]].x << ' ' << a[st[turn]].y << endl;
//            DEBUG(cur);

            res += cur;
        }

        swap(a[n], a[1]); --n;
        FOR(i,2,n) if (a[i].y < a[1].y || (a[i].y == a[1].y && a[i].x < a[1].x)) swap(a[1], a[i]);
        sort(a+2, a+n+1, cmp);

        if (sameLine()) res += 2;
        else {
            int last = n;
            while (last > 2 && ccw(a[1], a[last], a[last-1]) == 0) --last;
            reverse(a+last, a+n+1);

            FOR(i,n+1,n+n+n) a[i] = a[i-n];

            st[1] = 1;
            st[2] = 2;
            top = 2;
            FOR(i,3,n) {
                while (top >= 2 && ccw(a[st[top-1]], a[st[top]], a[i]) != RE_TRAI) {
                    --top;
                }
                st[++top] = i;
            }
            while (top >= 2 && ccw(a[st[top-1]], a[st[top]], a[1]) != RE_TRAI) --top;

            res += top;
        }

        answer(res, n+1);
    }
}
