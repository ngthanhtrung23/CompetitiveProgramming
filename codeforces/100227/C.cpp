
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

struct Frac {
    ll x, y;

    Frac() { x = 0; y = 1; }
    Frac(ll _x, ll _y) {
        ll g = __gcd(llabs(_x), llabs(_y));
        x = _x / g;
        y = _y / g;

        if (y < 0) {
            x = -x;
            y = -y;
        }
    }

    Frac operator + (const Frac& a) const {
        return Frac(x*a.y + y*a.x, y*a.y);
    }
    Frac operator - (const Frac& a) const {
        return Frac(x*a.y - y*a.x, y*a.y);
    }
    Frac operator * (const Frac& a) const {
        return Frac(x*a.x, y*a.y);
    }
    Frac operator / (const Frac& a) const {
        return Frac(x*a.y, y*a.x);
    }

    friend ostream& operator << (ostream& cout, const Frac& f) {
        if (f.y == 1) cout << f.x;
        else cout << f.x << '/' << f.y;
        return cout;
    }
};

Frac f[111], p[111], q[111];
Frac a[111][111];

void solve(int n) {
    REP(j,n) { // khu cot j
        int u = j;
        while (a[u][j].x == 0) ++u;

        REP(k,n+1) swap(a[u][k], a[j][k]);

        FOR(i,j+1,n-1) if (a[i][j].x) {
            Frac mult = a[i][j] / a[j][j];
            REP(k,n+1)
                a[i][k] = a[i][k] - a[j][k] * mult;
        }
    }

    FORD(i,n-1,0) {
        FOR(j,i+1,n-1)
            a[i][n] = a[i][n] - a[i][j] * q[j];
        q[i] = a[i][n] / a[i][i];
    }
}

void print(Frac a[], int n) {
    int cnt = 0;
    REP(i,n) if (a[i].x) {
        ++cnt;

        cout << '(' << a[i] << ',' << i << ") ";
    }
    if (cnt == 0) cout << "(0,0)";
    cout << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int m, n;
    while (cin >> m >> n && m && n) {
        REP(i,m+n) {
            cin >> f[i].x;
            f[i].y = 1;
        }
        // solve q
        REP(i,n) REP(j,n+1) a[i][j] = Frac(0, 1);

        FOR(target,m,m+n-1) {
            int row = target - m;
            REP(i,m+n) REP(j,n) {
                if (i + j == target) {
                    a[row][j] = a[row][j] + f[i];
                }
            }
            if (target == m+n-1) a[row][n] = Frac(1, 1);
            else a[row][n] = Frac(0, 1);
        }
        solve(n);

        // solve p
        REP(i,m) {
            p[i] = Frac(0, 1);
            REP(u,m+n) REP(v,n) {
                if (u + v == i) {
                    p[i] = p[i] + f[u] * q[v];
                }
            }
        }

        print(p, m);
        print(q, n);
        cout << '\n';
    }
}
