#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n, m, a[MN];
vector<int> ls[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) ls[i].clear();

        FOR(i,1,m) {
            cin >> a[i];
        }
        long long res = 0;
        FOR(i,1,m-1) {
            res += abs(a[i] - a[i+1]);

            if (a[i] != a[i+1]) {
                ls[a[i]].push_back(a[i+1]);
                ls[a[i+1]].push_back(a[i]);
            }
        }

        // DEBUG(res);
        long long sum = res;

        FOR(i,1,n) if (ls[i].size()) {
            sort(ls[i].begin(), ls[i].end());

            long long before = 0, after = 0;
            REP(t,ls[i].size()) before += abs(i - ls[i][t]);

            int u = ls[i][ls[i].size() / 2];
            REP(t,ls[i].size()) after += abs(u - ls[i][t]);

            res = min(res, sum - before + after);
        }
        cout << res << endl;
    }
    return 0;
}
