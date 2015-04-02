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
#define next __next
using namespace std;

ll next() {
    double x; cin >> x;
    return x * 100 + 0.5;
}

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    void read() { x = next(); y = next(); }
};

bool operator < (const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

bool operator == (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

map< tuple<ll, ll, ll>, vector< pair<Point,int> > > all;

tuple<ll, ll, ll> calc(Point A, Point B) {
    ll a, b, c;
    a = B.y - A.y;
    b = A.x - B.x;
    c = - (a*A.x + b*A.y);

    if (a < 0 || (a == 0 && b < 0)) {
        a = -a;
        b = -b;
        c = -c;
    }
    ll g = __gcd(__gcd(llabs(a), llabs(b)), llabs(c));
    a /= g;
    b /= g;
    c /= g;
    return make_tuple(a, b, c);
}

int n;

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n && n) {
        ++test;
        all.clear();
        FOR(i,1,n) {
            Point A, B; A.read(); B.read();
            if (B < A) swap(A, B);
            auto t = calc(A, B);

            if (all.count(t)) {
                all[t].push_back(make_pair(A, -1));
                all[t].push_back(make_pair(B, +1));
            }
            else {
                vector< pair<Point, int> > x;
                x.push_back(make_pair(A, -1));
                x.push_back(make_pair(B, +1));
                all[t] = x;
            }
        }

        int res = 0;
        for(auto ls : all) {
            auto cur = ls.second;
            sort(cur.begin(), cur.end());

            int sum = 0;
            for(auto p : cur) {
                sum += p.second;
                if (sum == 0) ++res;
            }
        }
        cout << res << "\n";
    }
    return 0;
}
