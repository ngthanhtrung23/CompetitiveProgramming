
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

int m[5], w[5];

int main() {
    REP(i,5) cin >> m[i];
    REP(i,5) cin >> w[i];
    int hs, hu;
    cin >> hs >> hu;
    ll sum = 0;
    REP(i,5) {
        int x = (i + 1) * 500;
        sum += max(x * 3 / 10, (x - m[i]*x / 250) - 50*w[i]);
    }
    sum += hs * 100;
    sum -= hu * 50;
    cout << sum << endl;
}
