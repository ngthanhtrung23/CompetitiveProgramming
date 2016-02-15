
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

const int MN = 100111;
struct Point {
    ll x, y;
    int id;
    ll norm() const { return x*x + y*y; }
} a[MN];

bool operator < (const Point& a, const Point& b) {
    return a.norm() < b.norm();
}
vector<Point> good;
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("nothingontv.in", "r", stdin);
    freopen("nothingontv.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
            a[i].x *= 2;
            a[i].y *= 2;
            a[i].id = i;
        }
        sort(a+1, a+n+1);

        good.clear();
        FOR(i,1,n) {
            ll Ox = a[i].x / 2;
            ll Oy = a[i].y / 2;
            ll r = Ox * Ox + Oy * Oy;

            bool ok = true;
            for(auto p : good) {
                ll dx = p.x - Ox;
                ll dy = p.y - Oy;
                if (dx * dx + dy * dy <= r) {
                    ok = false;
                    break;
                }
            }
            if (ok) good.push_back(a[i]);
        }

        cout << SZ(good) << endl;
        vector<int> res;
        for(auto p : good) res.push_back(p.id);
        sort(res.begin(), res.end());
        for(auto x : res) cout << x << ' '; cout << endl;
    }
}
