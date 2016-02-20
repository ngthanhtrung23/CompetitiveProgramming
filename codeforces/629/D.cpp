
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

#define double long double
const int MN = 100111;

struct Double {
    double x;
} c[MN];

int cmp(const double& a, const double& b) {
    if (fabs(a - b) < 1e-6) return 0;
    if (a < b) return -1;
    return 1;
}
int cmp(const Double& a, const Double& b) {
    return cmp(a.x, b.x);
}
bool operator < (const Double& a, const Double& b) {
    return cmp(a, b) < 0;
}
bool operator == (const Double& a, const Double& b) {
    return cmp(a, b) == 0;
}

double r[MN], h[MN], x[MN];
double f[MN], bit[MN];
int a[MN];
int n;

double get(int u) {
    double res = 0.0;
    for(int x = u; x > 0; x -= x & -x)
        res = max(res, bit[x]);
    return res;
}
void update(int u, double val) {
    for(int x = u; x < MN; x += x & -x)
        bit[x] = max(bit[x], val);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    while (cin >> n) {
        FOR(i,1,n) {
            cin >> r[i] >> h[i];
            x[i] = acos((double) -1.0) * r[i] * r[i] * h[i];
        }
//        PR(x, n);

        FOR(i,1,n) c[i].x = x[i];
        sort(c+1, c+n+1);

        int nc = unique(c+1, c+n+1) - c - 1;
//        FOR(i,1,nc) cout << c[i].x << ' '; cout << endl;

        FOR(i,1,n) {
            Double cur; cur.x = x[i];
            a[i] = lower_bound(c+1, c+nc+1, cur) - c;
        }
//        PR(a, n);

        double res = 0.0;
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            f[i] = get(a[i] - 1) + c[a[i]].x;
            update(a[i], f[i]);
            res = max(res, f[i]);
        }
        cout << res << endl;
    }
}
