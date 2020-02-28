// duel RR vs ngfam
// co can bat chrome cho cac ban xem ko nhi :))
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

int lab[100111];
int sum[100111];
struct DSU {
    void init(int n) {
        REP(i,n+2) lab[i] = -1;
        memset(sum, 0, sizeof sum);
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        sum[u] += sum[v];
        lab[v] = u;
        return true;
    }
} dsu;

const int MN = 100111;
int a[MN], added[MN], order[MN];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    // nani
    // DSU?
    // reverse order
    int n; cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> order[i];
    dsu.init(n);

    int res = 0;
    vector<int> ans;
    FORD(i,n,1) {
        ans.push_back(res);
        int id = order[i];

        added[id] = 1;
        assert(dsu.getRoot(id) == id);
        sum[dsu.getRoot(id)] = a[id];

        // connect
        if (added[id-1]) {
            dsu.merge(id-1, id);
        }
        if (added[id+1]) {
            dsu.merge(id, id+1);
        }

        res = max(res, sum[dsu.getRoot(id)]);
    }
    reverse(ans.begin(), ans.end());
    for (auto x : ans) cout << x << '\n';
    return 0;
}
