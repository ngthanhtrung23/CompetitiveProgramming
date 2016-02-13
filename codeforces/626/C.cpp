
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

int check(int n, int m, int maxh) {
    int x = maxh / 2;
    int y = maxh / 3;
    int z = maxh / 6;

    n -= min(n, x - z);
    m -= min(m, y - z);

    return n + m <= z;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        int l = 0, r = 1e7, res = 1e7;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(n, m, mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
}
