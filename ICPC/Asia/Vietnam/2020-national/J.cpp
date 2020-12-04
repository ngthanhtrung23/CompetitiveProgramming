#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

int calc(const vector<int>& h) {
    int n = h.size();
    vector<int> left(n), right(n);

    for (int i = 0; i < n; i++) {
        left[i] = h[i];
        if (i > 0) {
            left[i] = max(left[i], left[i-1]);
        }
    }

    for (int i = n-1; i >= 0; i--) {
        right[i] = h[i];
        if (i < n-1) {
            right[i] = max(right[i], right[i+1]);
        }
    }

    int res = 0;
    for (int i = 1; i < n-1; i++) {
        int border = min(left[i-1], right[i+1]);
        if (border > h[i]) res += border - h[i];
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, total; cin >> n >> total;
    vector<int> h(n);
    for (int& x : h) {
        cin >> x;
    }

    int res = calc(h);
    REP(i,n) FOR(j,i+1,n-1) FOR(k,j+1,n-1) {
        FOR(left,0,total) FOR(mid,0,total-left) {
            int right = total - left - mid;
            assert(right >= 0);

            h[i] += left;
            h[j] += mid;
            h[k] += right;

            res = max(res, calc(h));

            h[i] -= left;
            h[j] -= mid;
            h[k] -= right;
        }
    }
    cout << res << endl;
}
