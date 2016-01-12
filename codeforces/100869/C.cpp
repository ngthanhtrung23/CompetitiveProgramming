
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

int n;
ll a[100111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        ll P;
        cin >> n >> P;
        FOR(i,1,n) {
            cin >> a[i];
            a[i] += a[i-1];
        }
        ll res = 0;
        int j = 1;
        FOR(i,1,n) {
            while (a[i] - a[j-1] > P) ++j;
            if (j <= i) {
                res += i - j + 1;
            }
        }
        cout << "Case #" << test << ": " << res << endl;
    }
}