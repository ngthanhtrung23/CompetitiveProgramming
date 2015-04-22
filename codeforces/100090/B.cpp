#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

#define ll long long

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
} a[200111];
int n;

inline int next(int u) {
    if (u == n) return 1;
    else return u + 1;
}

ll area() {
    ll res = 0;
    FOR(i,1,n) {
        int j = next(i);
        res += a[i].x*a[j].y - a[i].y*a[j].x;
    }
    return llabs(res);
}

ll area2(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    return llabs(b.x*c.y - b.y*c.x);
}

ll best_diff;
int savei, savej;
void update(ll cur, int i, int j) {
    if (cur < best_diff) {
        best_diff = cur;
        savei = i;
        savej = j;
    }
}

void update(ll S1, ll S2, int i, int j) {
    update(llabs(S1 - S2), i, j);
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%I64d%I64d", &a[i].x, &a[i].y);

        ll S = area();

        int j = 2;
        ll S1 = 0, S2 = S;

        best_diff = S;
        savei = 1;
        savej = 2;

        FOR(i,1,n) {
            if (j == i) {
                j = next(j);
                S1 = 0;
                S2 = S;
            }
            update(S1, S2, i, j);
            while (S1 < S2) {
                update(S1, S2, i, j);

                int jj = next(j);
                ll R1 = S1 + area2(a[i], a[j], a[jj]);
                ll R2 = S2 - area2(a[i], a[j], a[jj]);

                if (R1 >= R2) {
                    update(R1, R2, i, jj);
                    break;
                }

                j = jj;
                S1 = R1;
                S2 = R2;
            }

            ll cur = area2(a[i], a[next(i)], a[j]);
            S1 -= cur;
            S2 += cur;
        }
        cout << savei << ' ' << savej << endl;
    }
    return 0;
}
