#include "bits/stdc++.h"
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

struct Number {
    int sign;
    double val;
};
bool operator < (const Number& a, const Number& b) {
    if (a.sign < b.sign) return a.sign < b.sign;

    if (a.sign < 0) return a.val > b.val;  // negative
    if (a.sign > 0) return a.val < b.val;  // positive
    return false; // 0
}

int main() {
    // input
    int n; cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // find largest prod
    pair<Number, int> res {Number{-1, -1e100}, -1};
    for (int i = -1; i < n; i++) {  // element to remove; -1 -> remove nothing
        Number prod{1, 0.0};
        for (int j = 0; j < n; j++) {
            if (j == i) continue;

            int x = a[j];
            if (x == 0) {
                prod.sign = 0;
                prod.val = 0.0;
                continue;
            }
            if (x < 0) {
                prod.sign = -prod.sign;
                x = -x;
            }

            prod.val += log(x);
        }

        if (res.first < prod) {
            res = {prod, i};
        }
    }

    // output
    const int MOD = 1e9 + 7;
    long long prod = 1;
    for (int i = 0; i < n; i++) {
        if (i == res.second) continue;

        prod = prod * a[i] % MOD;
    }
    cout << prod << endl;
}
