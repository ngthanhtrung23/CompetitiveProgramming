
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int a[100111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        multiset<int> all;
        int j = 1, res = 0;
        FOR(i,1,n) {
            all.insert(a[i]);
            while (*all.rbegin() - *all.begin() > 1) {
                all.erase(all.find(a[j]));
                ++j;
            }
            res = max(res, i - j + 1);
        }
        cout << res << endl;
    }
}
