#include "bits/stdc++.h"
using namespace std;

#define int long long
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

struct Item {
    double position;
    int from, to;
};

double sqr(double x) {
    return x*x;
}
 
int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    int n; cin >> n;
    vector<double> a(n);
    for (auto& x : a) cin >> x;

    vector<double> sum(n);
    std::partial_sum(a.begin(), a.end(), sum.begin());

    auto get_sum = [sum] (int from, int to) {
        if (from == 0) return sum[to];
        return sum[to] - sum[from - 1];
    };

    // go through elements from left -> right
    // keep track of 'Items'. Each item = range of elements in final
    // result.
    //
    // For i-th element:
    // - try putting it at a[i]
    // - if a[i] < previous item's position --> merge previous item
    //   with this element
    // - repeat this until items' positions are increasing
    vector<Item> res;
    for (int i = 0; i < n; i++) {
        // Create new item for this element
        Item item {a[i], i, i};

        // merge with previous element(s) if needed
        while (!res.empty() && res.back().position > item.position) {
            item.from = res.back().from;
            item.position = get_sum(item.from, i) / (double) (i - item.from + 1);
            res.pop_back();
        }
        res.push_back(item);
    }

    double cost = 0.0;
    for (auto item : res) {
        for (int i = item.from; i <= item.to; i++) {
            cost += sqr(a[i] - item.position);
        }
    }
    cout << (fixed) << setprecision(9) << sqrt(cost) << endl;

    return 0;
}
