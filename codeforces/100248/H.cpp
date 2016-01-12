
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

struct Rect {
    int x1, y1, x2, y2;

    void read() {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    }
} a[111];

bool intersect(const Rect& a, const Rect& b) {
    if (a.x2 <= b.x1 || b.x2 <= a.x1) return false;
    if (a.y2 <= b.y1 || b.y2 <= a.y1) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int X, Y; cin >> X >> Y;
        int n; cin >> n;
        FOR(i,1,n) a[i].read();

        bool ok = true;
        FOR(i,1,n) FOR(j,i+1,n) if (intersect(a[i], a[j])) {
            ok = false;
            break;
        }
        if (!ok) {
            puts("NONDISJOINT");
            continue;
        }
        FOR(i,1,n) {
            if (a[i].x1 < 0 || a[i].x2 > X
                    || a[i].y1 < 0 || a[i].y2 > Y) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            puts("NONCONTAINED");
            continue;
        }
        ll area = X * Y;
        FOR(i,1,n) area -= (a[i].x2 - a[i].x1) * (a[i].y2 - a[i].y1);
        if (area) {
            puts("NONCOVERING");
            continue;
        }
        puts("OK");
    }
}
