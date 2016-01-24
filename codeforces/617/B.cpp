
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

int a[111], n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        int sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i];
        }
        if (sum == 0) {
            cout << 0 << endl;
            continue;
        }
        ll res = 1;
        FOR(i,1,n) if (a[i]) {
            FOR(j,i+1,n) if (a[j]) {
                res = res * (j - i);
                break;
            }
        }
        cout << res << endl;
    }
}
