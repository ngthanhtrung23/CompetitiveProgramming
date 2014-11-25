#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    long long n;
    while (cin >> n) {
        if (n == 0) {
            cout << 1 << endl;
            continue;
        }
        long long x = 0;
        int res = 1;
        for(long long y = n-1; y >= 1; --y) {
            long long lastx = x;
            while (y*y + (x+1)*(x+1) <= n*n) {
                ++x;
            }
            res += max(x - lastx, 1LL);
        }
        cout << 4*res << endl;
    }
    return 0;
}

