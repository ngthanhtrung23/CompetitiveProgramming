
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

const int MN = 500111;
int n, k, a[MN];

bool checkMin(int x) {
    int need = 0;
    FOR(i,1,n) if (a[i] < x) need += x - a[i];
    return need <= k;
}
bool checkMax(int x) {
    int need = 0;
    FOR(i,1,n) if (a[i] > x) need += a[i] - x;
    return need <= k;
}

int getNewMin() {
    int l = 0, r = 1000111000, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (checkMin(mid)) {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return res;
}
int getNewMax() {
    int l = 0, r = 1000111000;
    int res = r;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (checkMax(mid)) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(k) == 1) {
        FOR(i,1,n) GI(a[i]);

        int newMin = getNewMin();
        int newMax = getNewMax();

        int sum = 0;
        FOR(i,1,n) sum += a[i];

        if (newMin > newMax) newMin = newMax;
        int res = newMax - newMin;
        if (sum % n && res == 0) res = 1;

        cout << res << endl;
    }
}
