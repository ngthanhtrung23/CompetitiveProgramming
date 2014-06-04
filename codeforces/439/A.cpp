#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n, d, a[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> d) {
        int sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i];
            if (i < n) sum += 10;
        }
        if (sum > d) {
            cout << -1 << endl;
        }
        else {
            int ln = (n-1) * 2;
            d -= sum;
            ln += d / 5;
            cout << ln << endl;
        }
    }
    return 0;
}
