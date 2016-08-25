#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

int a00, a01, a10, a11;

int getn(int s) {
    int n = (int) (sqrt(s * 2));
    while (n * (n-1) > 2*s) --n;
    while (n * (n-1) < 2*s) ++n;
    if (n * (n-1) == 2*s) return n;
    else return -1;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> a00 >> a01 >> a10 >> a11) {
        int sum = a00 + a01 + a10 + a11;
        if (sum == 0) {
            cout << "0" << endl;
            continue;
        }
        int n = getn(sum);
        if (n < 0) {
            cout << "Impossible" << endl;
            continue;
        }

        int c0 = getn(a00);
        int c1 = getn(a11);

        if (c0 < 0 || c1 < 0) {
            cout << "Impossible" << endl;
            continue;
        }

        if (c0 == 0 && c0 + c1 < n) ++c0;
        if (c1 == 0 && c0 + c1 < n) ++c1;

        if (c0 + c1 != n) {
            cout << "Impossible" << endl;
            continue;
        }

        REP(turn,n) {
            if (c1 && a10 >= c0) {
                cout << '1';
                --c1;
                a10 -= c0;
            } else {
                cout << '0';
                --c0;
                a01 -= c1;
            }
        }
        cout << endl;
    }
}
