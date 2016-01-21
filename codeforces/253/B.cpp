
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

int cnt[5011];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            int x; cin >> x;
            cnt[x]++;
        }
        FOR(i,1,5000) cnt[i] += cnt[i-1];
        int res = 0;
        FOR(start,1,2500) {
            res = max(res, cnt[2*start] - cnt[start - 1]);
        }
        cout << n - res << endl;
    }
}
