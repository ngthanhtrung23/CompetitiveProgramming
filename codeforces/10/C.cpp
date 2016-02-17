
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

int d(int x) {
    int res = x % 9;
    if (res == 0) res = 9;
    return res;
}

ll cnt[11];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) cnt[d(i)]++;

        ll all = 0;
        FOR(da,1,9) FOR(db,1,9) {
            int dc = d(da * db);

            all += cnt[da] * cnt[db] * cnt[dc];
        }
        ll good = 0;
        FOR(a,1,n) good += n / a;
        cout << all - good << endl;
    }
}
