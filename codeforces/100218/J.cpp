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
#define double long double
using namespace std;

int n;
const int MN = 1011;

ll best = 1e15;
int save1, save2, save3;

struct Point {
    ll x, y;
    int id;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }

    ll sqlen() {
        return x*x + y*y;
    }
} a[MN];

bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

void update(const Point &A, const Point &B, const Point &C) {
    Point vb = B - A;
    Point vc = C - A;

    ll cur = vb.y*vc.x - vb.x*vc.y;
    if (cur < 0) cur = -cur;

    if (cur < best) {
        best = cur;
        save1 = A.id;
        save2 = B.id;
        save3 = C.id;
    }
}

Point cur[MN];

const double EPS = 1e-12;
const double INF = 1e9;

int cmp(double x, double y) {
    if (fabs(x - y) < EPS) return 0;
    if (x < y) return -1;
    return 1;
}

// ------------------------ BASIC TYPE
struct D {
    double x;

    D() {}
    D(double x) : x(x) {}

    D operator + (const D& a) const { return D(x+a.x); }
    D operator - (const D& a) const { return D(x-a.x); }
    D operator * (const D& a) const { return D(x*a.x); }
    D operator / (const D& a) const { return D(x/a.x); }

    D operator - () const { return D(-x); }

    D& operator += (const D& a) { return *this = *this + a; }
    D& operator -= (const D& a) { return *this = *this - a; }
    D& operator *= (const D& a) { return *this = *this * a; }
    D& operator /= (const D& a) { return *this = *this / a; }

    bool operator == (const D& a) const { return cmp(x, a.x) == 0; }
    bool operator <= (const D& a) const { return cmp(x, a.x) <= 0; }
    bool operator >= (const D& a) const { return cmp(x, a.x) >= 0; }
    bool operator <  (const D& a) const { return cmp(x, a.x) <  0; }
    bool operator >  (const D& a) const { return cmp(x, a.x) >  0; }
    bool operator != (const D& a) const { return cmp(x, a.x) != 0; }

    int sign() {
        int t = cmp(x, 0);
        if (t == 0) return 0;
        if (t < 0) return -1;
        return 1;
    }

    friend istream& operator >> (istream& cin, D& x) {
        cin >> x.x;
        return cin;
    }
    friend ostream& operator << (ostream& cout, D& x) {
        cout << x.x;
        return cout;
    }
};
int cmp(const D& a, const D& b) {
    return cmp(a.x, b.x);
}

D sqrt(D x) { assert(x >= 0); return D(sqrt(x.x)); }
D abs(D x) { if (x < 0) return -x; else return x; }
D fabs(D x) { if (x < 0) return -x; else return x; }
D sin(D x) { return sin(x.x); }
D cos(D x) { return cos(x.x); }
D tan(D x) { return tan(x.x); }
D asin(D x) { assert(D(-1) <= x && x <= D(1)); return asin(x.x); }
D acos(D x) { assert(D(-1) <= x && x <= D(1)); return acos(x.x); }
D atan(D x) { return atan(x.x); }

D f[MN], x[MN];
int ff[MN];

pair<ll,int> all[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].id = i;
        }
        best = 1e15;
        FOR(i,1,n) {
            Point O = a[i];
            int k = 0;
            FOR(j,1,n) if (j != i)
            if (a[j].y > O.y || (a[j].y == O.y && a[j].x > O.x)) {
                ++k;
                cur[k] = a[j];
                f[k] = D(atan2(a[j].y - O.y, a[j].x - O.x));
                x[k] = f[k];
            }
            sort(x+1, x+k+1);
            int nx = unique(x+1, x+k+1) - x - 1;
            FOR(j,1,k) ff[j] = lower_bound(x+1, x+nx+1, f[j]) - x;

//            DEBUG(i);
//            FOR(j,1,k) {
//                cout << cur[j].x << ' ' << cur[j].y << ' ' << ff[j] << endl;
//            }

            FOR(j,1,k) all[j] = make_pair((a[j] - O).sqlen(), j);
            sort(all+1, all+k+1);

            map<int,int> mp;
            FOR(j,1,k) {
                int id = all[j].second;
                int alpha = ff[id];

                auto it = mp.lower_bound(alpha+1);
                if (it != mp.end()) {
                    int id2 = it->second;
                    update(O, cur[id], cur[id2]);
                }

                it = mp.lower_bound(alpha);
                if (it != mp.begin()) {
                    --it;
                    int id2 = it->second;
                    update(O, cur[id], cur[id2]);
                }

                if (!mp.count(alpha)) mp[alpha] = id;
            }
        }
        cout << save1 << ' ' << save2 << ' ' << save3 << endl;
    }
}
