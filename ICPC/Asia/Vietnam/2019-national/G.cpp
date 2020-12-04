#include "bits/stdc++.h"
using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define int long long

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

int get_sum(const vector<int>& sum, int l, int r) {
    return sum[r] - sum[l-1];
}

int use_portal(int left, int right, const vector<int>& sum, const vector<int>& a) {
    int mid = (left + right) / 2;
    return a[mid] * (mid - left + 1) - get_sum(sum, left, mid)
        + get_sum(sum, mid+1, right) - a[mid] * (right - mid);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n; cin >> n;
    vector<int> a(n + 1);
    FOR(i,1,n) cin >> a[i];
    sort(a.begin() + 1, a.begin() + n + 1);

    vector<int> sum(n + 1);
    vector<int> sum_abs(n + 1);

    FOR(i,1,n) {
        sum[i] = sum[i-1] + a[i];
        sum_abs[i] = sum_abs[i-1] + llabs(a[i]);
    }
    int res = sum_abs[n];

    FOR(i,1,n) {
        // 1 --> i: use portal
        int cur = get_sum(sum_abs, i+1, n) + use_portal(1, i, sum, a);
        res = min(res, cur);

        // i --> n: use portal
        cur = get_sum(sum_abs, 1, i-1) + use_portal(i, n, sum, a);
        res = min(res, cur);
    }

    cout << res << endl;
    return 0;
}
