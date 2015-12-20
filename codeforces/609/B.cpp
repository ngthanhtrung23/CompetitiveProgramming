
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

int cnt[111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        memset(cnt, 0, sizeof cnt);
        while (n--) {
            int x; cin >> x;
            cnt[x]++;
        }
        ll res = 0;
        FOR(i,1,m) FOR(j,i+1,m)
            res += cnt[i] * (ll) cnt[j];
        cout << res << endl;
    }
}
