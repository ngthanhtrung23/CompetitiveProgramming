
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 5011;
int sum[MN], diff[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        memset(sum, 0, sizeof sum);
        memset(diff, 0, sizeof diff);
        FOR(i,1,n) {
            int x, y; cin >> x >> y;
            sum[x + y] ++;
            diff[x - y + 1000]++;
        }

        ll res = 0;
        REP(i,MN) {
            res = res + sum[i] * (sum[i] - 1) / 2;
            res = res + diff[i] * (diff[i] - 1) / 2;
        }
        cout << res << endl;
    }
}
