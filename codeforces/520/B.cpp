
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

int d[20111];

int main() {
    int n, m;
    while (cin >> n >> m) {
        memset(d, -1, sizeof d);
        queue<int> qu;
        qu.push(n);
        d[n] = 0;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            if (2*u < 20111 && d[2*u] < 0) {
                d[2*u] = d[u] + 1;
                qu.push(2*u);
            }
            if (u-1 > 0 && d[u-1] < 0) {
                d[u-1] = d[u] + 1;
                qu.push(u-1);
            }
        }
        cout << d[m] << endl;
    }
    return 0;
}

