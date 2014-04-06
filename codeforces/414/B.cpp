#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MOD = 1000000007;
const int MN = 2011;

int f[MN][MN];
vector<int> ls[MN];

void update(int &x, int k) {
    x += k;
    while (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    int sum = 0;
    FOR(i,1,2000) {
        FOR(j,1,i) if (i % j == 0) ls[i].push_back(j);
        sum += ls[i].size();
    }
    // DEBUG(sum);
    int n, k;
    while (cin >> n >> k) {
        memset(f, 0, sizeof f);
        FOR(x,1,n) f[1][x] = 1;

        FOR(i,2,k) {
            FOR(x,1,n) {
                f[i][x] = 0;
                REP(t,ls[x].size()) {
                    int y = ls[x][t];
                    update(f[i][x], f[i-1][y]);
                }
            }
        }

        int res = 0;
        FOR(x,1,n) update(res, f[k][x]);
        cout << res << endl;
    }
    return 0;
}
