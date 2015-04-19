
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
using namespace std;

struct Fraction {
    ll x, y;

    Fraction(ll k) : x(k), y(1) {}

    Fraction(ll _x, ll _y) : x(_x), y(_y) {
        ll g = __gcd(x, y);
        x /= g;
        y /= g;

        if (y < 0) {
            x = -x;
            y = -y;
        }
    }

    Fraction operator + (const Fraction& a) const {
        return Fraction(x*a.y + y*a.x, y*a.y);
    }

    Fraction operator - (const Fraction& a) const {
        return Fraction(x*a.y - y*a.x, y*a.y);
    }

    Fraction operator * (const Fraction& a) const {
        return Fraction(x*a.x, y*a.y);
    }

    Fraction operator / (const Fraction& a) const {
        return Fraction(x*a.y, y*a.x);
    }

    Fraction inverse() const { return Fraction(y, x); }

    string toString() {
        stringstream ss; ss << x << '/' << y;
        return ss.str();
    }
};

struct Cont {
    vector<ll> a;

    void read(int n) {
        a.resize(n);
        REP(i,n) cin >> a[i];
    }

    void print() {
        for(ll x : a) cout << x << ' '; cout << '\n';
    }

    Fraction toFrac() {
        Fraction res = a[a.size()-1];
        FORD(i,a.size()-2,0) {
            res = res.inverse() + Fraction(a[i]);
        }
        return res;
    }
};

Cont toCont(Fraction f) {
    Cont res;
    res.a.clear();
    if (f.x == 0) {
        res.a.push_back(0);
        return res;
    }
    if (f.x % f.y == 0) {
        res.a.push_back(f.x / f.y);
        return res;
    }
    while (f.x) {
        if (f.x < 0) {
            ll t = f.x / f.y - 1;
            res.a.push_back(t);
            f.x -= t * f.y;
        }
        else {
            res.a.push_back(f.x / f.y);
            f.x %= f.y;
        }
        if (!f.x) break;
        f = f.inverse();
    }
    return res;
}

void test() {
    Cont x; x.a = vector<ll> {5, 1, 1, 2};
    Fraction f = x.toFrac();
    assert(f.x == 28 && f.y == 5);

    x.a = vector<ll> {5, 2, 2};
    f = x.toFrac();
    assert(f.x == 27 && f.y == 5);

    f = Fraction(275, 25);
    assert(f.x == 11 && f.y == 1);
}

int main() {
    ios :: sync_with_stdio(false);
    test();
    int n1, n2;
    int test = 0;
    while (cin >> n1 >> n2 && n1 && n2) {
        Cont a, b;
        a.read(n1);
        b.read(n2);

        Fraction fa = a.toFrac();
        Fraction fb = b.toFrac();

        cout << "Case " << ++test << ":\n";
        toCont(fa + fb).print();
        toCont(fa - fb).print();
        toCont(fa * fb).print();
        toCont(fa / fb).print();
    }
    return 0;
}
