
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m > n) swap(m, n);
        if (m == 1) cout << n << endl;
        else if (m == 2) {
            if (n % 4 == 1) cout << n + 1 << endl;
            else if (n % 4 == 2) cout << n + 2 << endl;
            else if (n % 4 == 3) cout << n + 1 << endl;
            else cout << n << endl;
        }
        else cout << (m*n) / 2 + (m*n) % 2 << endl;
    }
    return 0;
}
