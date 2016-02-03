
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

double x, y, z;
double res;
string save;

double EPS = 1e-6;
double tower(double x, double y, double z) {
    if (fabs(x - 1) < EPS) return -1e10;
    if (x < 1 - EPS) return -1e11;
    return z * log(y) + log(log(x));
}

double power(double x, double y, double z) {
    if (fabs(x - 1) < EPS) return -1e10;
    if (x < 1 - EPS) return -1e11;
    return log(z) + log(y) + log(log(x));
}

void update(double val, string t) {
    if (val > res) {
        res = val;
        save = t;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> x >> y >> z) {
        res = -1e12;
        if (x < 1 - EPS && y < 1 - EPS && z < 1 - EPS) {
            update(- tower(1.0 / x, y, z), "x^y^z");
            update(- tower(1.0 / x, z, y), "x^z^y");
            update(- power(1.0 / x, y, z), "(x^y)^z");

            update(- tower(1.0 / y, x, z), "y^x^z");
            update(- tower(1.0 / y, z, x), "y^z^x");
            update(- power(1.0 / y, z, x), "(y^x)^z");

            update(- tower(1.0 / z, x, y), "z^x^y");
            update(- tower(1.0 / z, y, x), "z^y^x");
            update(- power(1.0 / z, x, y), "(z^x)^y");

            cout << save << endl;
            continue;
        }
        update(tower(x, y, z), "x^y^z");
        update(tower(x, z, y), "x^z^y");
        update(power(x, y, z), "(x^y)^z");

        update(tower(y, x, z), "y^x^z");
        update(tower(y, z, x), "y^z^x");
        update(power(y, z, x), "(y^x)^z");

        update(tower(z, x, y), "z^x^y");
        update(tower(z, y, x), "z^y^x");
        update(power(z, x, y), "(z^x)^y");

        cout << save << endl;
    }
}
