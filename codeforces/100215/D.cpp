
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 1011;

struct Poly {
    bitset<MN> x;
    int deg;

    bool read() {
        if (!(cin >> deg)) return false;
        x.reset();

        FORD(i,deg,0) {
            int u; cin >> u;
            if (u) x.set(i);
        }
        return true;
    }

    void print() {
        cout << deg;
        FORD(i,deg,0) cout << ' ' << x.test(i);
        cout << endl;
    }
} a1, b1, c1, a2, b2, c2, x, y, dx, dy, d;

Poly operator + (const Poly& a, const Poly& b) {
    Poly res;
    res.deg = max(a.deg, b.deg);
    res.x.reset();
    FORD(i,res.deg,0) {
        if (a.x.test(i) ^ b.x.test(i))
            res.x.set(i);
    }
    while (res.deg >= 0 && !res.x.test(res.deg)) --res.deg;
    return res;
}

Poly operator << (const Poly& a, int k) {
    Poly res;
    res.deg = a.deg + k;
    res.x = a.x << k;
    return res;
}


Poly operator * (const Poly& a, const Poly& b) {
    Poly res;
    res.deg = 0;
    res.x.reset();
    FOR(i,0,a.deg)
        if (a.x.test(i))
            res = res + (b << i);
    while (res.deg >= 0 && !res.x.test(res.deg)) --res.deg;
    return res;
}

Poly operator / (Poly a, const Poly& b) {
    Poly res;
    if (b.deg == 0) return a;

    res.deg = a.deg - b.deg;
    res.x.reset();

    while (a.deg >= b.deg) {
        int u = a.deg - b.deg;
        res.x.set(u);

        a = a + (b << u);
    }

    return res;
}

Poly operator % (Poly a, const Poly& b) {
    if (b.deg == 0) {
        Poly res;
        res.deg = -1;
        res.x.reset();
        return res;
    }

    while (a.deg >= b.deg) {
        int u = a.deg - b.deg;

        a = a + (b << u);
    }

    return a;
}

Poly extgcd(Poly a, Poly b, Poly &x, Poly &y) {
    Poly g = a;
    x.deg = 0; x.x.reset(); x.x.set(0);
    y.deg = -1; y.x.reset();

    if (b.deg >= 0) {
        g = extgcd(b, a % b, y, x);
        y = y + (a / b) * x;
    }
    return g;
}

bool operator == (const Poly& a, const Poly& b) {
    if (a.deg != b.deg) return false;
    REP(i,a.deg) if (a.x.test(i) != b.x.test(i)) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);

    while (a1.read() && b1.read() && c1.read()
            && a2.read() && b2.read() && c2.read()) {
        d = a1*b2 + a2*b1;
        dx = b1*c2 + b2*c1;
        dy = c1*a2 + c2*a1;

        if (d.deg >= 0) {
            if ((dx % d).deg >= 0 || (dy % d).deg >= 0) {
                cout << "No solution\n";
            }
            else {
                x = dx / d;
                y = dy / d;

                x.print();
                y.print();
            }
        }
        else {
            if (a1.deg < 0 && b1.deg < 0) {
                swap(a1, a2);
                swap(b1, b2);
                swap(c1, c2);
            }
            if (dx.deg < 0 && dy.deg < 0) {
                Poly tx, ty;
                Poly g = extgcd(a1, b1, tx, ty);

                if (g.deg < 0) {
                    g.deg = 0;
                }

                if ((c1 % g).deg >= 0) {
                    cout << "No solution\n";
                }
                else {
                    Poly mult = c1 / g;
                    x = tx * mult;
                    y = ty * mult;

                    if (a1 * x + b1 * y == c1 && a2 * x + b2 * y == c2) {
                        x.print();
                        y.print();
                    }
                    else {
                        cout << "No solution\n";
                    }
                }
            }
            else {
                cout << "No solution\n";
            }
        }
//        cout << "----" << endl;
    }
}