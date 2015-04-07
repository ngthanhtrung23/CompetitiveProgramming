
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 1000111;
const int MOD = 1000000007;

int n, m, k;
int p2[MN];

int main() {
    ios :: sync_with_stdio(false);
    p2[0] = 1;
    FOR(i,1,MN-1) p2[i] = p2[i-1] * 2 % MOD;

    while (cin >> n >> m >> k) {
        vector<int> x;
        bool ok = true;
        while (m--) {
            int u, v; cin >> u >> v;
            if (u+1 == v) {
            }
            else if (u+k+1 == v) {
                x.push_back(u);
            }
            else {
                ok = false;
            }
        }
        if (!ok) {
            cout << 0 << endl;
            continue;
        }

        int res = 0;
        if (x.empty()) {
            res = 1;
            FOR(i,1,n-k-1) {
                int from = i + 1;
                int to = min(i + k, n - k - 1);
                res = (res + p2[to - from + 1]) % MOD;
            }
        }
        else {
            sort(x.begin(), x.end());
            int a = *x.begin(), b = x.back();
            if (a + k + 1 <= b) {
                res = 0;
            }
            else {
                res = 0;
                FOR(i,1,n-k-1) {
                    int from = i;
                    int to = min(i + k, n - k - 1);

                    if (a >= from && b <= to) {
                        if (a == i) {
                            res = (res + p2[to - from - x.size() + 1]) % MOD;
                        }
                        else {
                            res = (res + p2[to - from - x.size()]) % MOD;
                        }
                    }
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
