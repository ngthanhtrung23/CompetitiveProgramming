#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        if (n < 2) {
            if (k == 0) {
                cout << 1 << endl;
            }
            else {
                cout << -1 << endl;
            }
            continue;
        }

        if (n / 2 <= k) {
            int first = k - (n/2-1);
            cout << first << ' ' << first + first << ' ';
            int cur = first + first + 1;
            FOR(i,2,n/2) {
                cout << cur << ' ' << cur + 1 << ' ';
                cur += 2;
            }
            if (n % 2 == 1) {
                cout << cur + 1 << ' ';
            }
            cout << endl;
        }
        else {
            cout << -1 << endl;
        }
    }
    return 0;
}