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
    int n, cap;
    while (cin >> n >> cap) {
        int sum = 0, ln = 0;
        FOR(i,1,n) {
            int a; cin >> a;
            sum += a;
            ln = max(ln, a);
        }
        if (sum - ln <= cap) cout << "YES"; else cout << "NO";
        cout << endl;
    }
    return 0;
}
