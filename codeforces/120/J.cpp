
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

#define MN 100111
struct Point {
    ll x, y;
    int k;
    int id;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    ll sqlen() { return x*x + y*y; }
} a[MN];

ll mindist; // will be the result
int savei, savej, savek1, savek2;

void upd_ans(Point a, Point b) {
    ll cur = (a - b).sqlen();
    if (cur < mindist) {
        mindist = cur;
        savei = a.id;
        savej = b.id;

        savek1 = a.k;
        savek2 = 5 - b.k;
    }
}

bool cmpx(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool cmpy(const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

void rec(int l, int r, Point a[]) {
    if (r - l <= 3) {
        for (int i=l; i<=r; ++i)
            for (int j=i+1; j<=r; ++j)
                    upd_ans(a[i], a[j]);
        sort(a+l, a+r+1, cmpy); // compare by y
        return;
    }

    int m = (l + r) >> 1;
    int midx = a[m].x;
    rec(l, m, a), rec(m+1, r, a);
    static Point t[MN];
    merge(a+l, a+m+1, a+m+1, a+r+1, t, cmpy); // compare by y
    copy(t, t+r-l+1, a+l);

    int tsz = 0;
    for (int i=l; i<=r; ++i)
        if (fabs(a[i].x - midx) < mindist) {
            for (int j=tsz-1; j>=0 && a[i].y - t[j].y < mindist; --j)
                upd_ans(a[i], t[j]);
            t[tsz++] = a[i];
        }
}

int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            int x, y; scanf("%d%d", &x, &y);
            a[i].x = abs(x);
            a[i].y = abs(y);
            a[i].id = i;

            if (x >= 0 && y >= 0) a[i].k = 1;
            else if (x < 0 && y >= 0) a[i].k = 2;
            else if (x >= 0 && y < 0) a[i].k = 3;
            else a[i].k = 4;
        }
        mindist = 1e12;
        sort(a+1, a+n+1, cmpx);
        rec(1, n, a);

        cout << savei << ' ' << savek1 << ' ' << savej << ' ' << savek2 << endl;
    }
}
