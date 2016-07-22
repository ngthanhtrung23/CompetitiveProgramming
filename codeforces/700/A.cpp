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
int n, l, v1, v2, k;
int group;

bool check(double t) {
    double t2 = (l - t * v1) / (v2 - v1);

    double dist = t2 * (v2 - v1);
    double gap = dist / (v1 + v2);

    return t2 * group + gap * (group - 1) <= t;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> l >> v1 >> v2 >> k) {
        group = (n + k - 1) / k;
        double left = 0.0, right = l / (double) v1;
        REP(turn,100) {
            double mid = (left + right) / 2.0;
            if (check(mid)) right = mid;
            else left = mid;
        }
        cout << left << endl;
    }
}
