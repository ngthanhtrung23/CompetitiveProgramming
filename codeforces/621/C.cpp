
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

const int MN = 100111;
int n, p, l[MN], r[MN], good[MN];

int cnt(int l, int r) {
    if (l % p) l = l - l % p + p;
    if (r % p) r -= r % p;
    if (l > r) return 0;
    return (r - l) / p + 1;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> p) {
        FOR(i,1,n) {
            cin >> l[i] >> r[i];
            good[i] = cnt(l[i], r[i]);
        }
        double res = 0.0;
        FOR(i,1,n) {
            double p = 1.0;
            int j = i % n + 1;

            p *= 1.0 - good[i] / (double) (r[i] - l[i] + 1);
            p *= 1.0 - good[j] / (double) (r[j] - l[j] + 1);

            p = 1.0 - p;

            res += p * 2000;
        }
        cout << (fixed) << setprecision(9) << res << endl;
    }
}
