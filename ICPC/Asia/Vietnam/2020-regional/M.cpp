#include "bits/stdc++.h"
#include <iomanip>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

void pour(bool is_final, int k, vector<double>& vals, const vector<pair<int, double>>& pours) {
    cout << (is_final ? "FINAL" : "POUR") << ' ';
    cout << SZ(pours) << ' ';
    for (const auto [cup_id, amount] : pours) {
        cout << cup_id << ' ' << amount << ' ';
        vals[cup_id] += amount;
    }
    cout << endl;

    if (is_final) return;

    int start_id; cin >> start_id;
    FOR(i, start_id, start_id + k - 1) {
        vals[i] = 0;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cout << (fixed) << setprecision(9);
    int n, k, x; cin >> n >> k >> x;
    vector<double> vals(n+1, 0.0);

    int nGroup = (n - 1) / k + 1;
    REP(turn,1900) {
        vector< pair<int, double> > pours;
        double cur_sum = 0.0;
        for (int i = 1; i <= n; i += k) {
            cur_sum += vals[i];
        }
        double next_sum = cur_sum + x;
        for (int i = 1; i <= n; i += k) {
            pours.push_back({i, next_sum / nGroup - vals[i]});
        }

        pour((nGroup == 1 && turn == 1899), k, vals, pours);
    }

    FORD(n_max, nGroup-1,1) {
        vector< pair<double, int> > cups;
        for (int i = 1; i <= n; i += k) {
            cups.push_back({vals[i], i});
        }
        sort(cups.begin(), cups.end());

        vector< pair<int, double> > pours;
        FOR(i, SZ(cups) - n_max, SZ(cups) - 1) {
            auto [val, cup_id] = cups[i];
            pours.push_back({cup_id, x * 1.0 / n_max});
        }
        pour(n_max == 1, k, vals, pours);
    }

    return 0;
}

