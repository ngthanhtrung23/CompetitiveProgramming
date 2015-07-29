
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int a[22];

int main() {
    ios :: sync_with_stdio(false);
    freopen("factor.in", "r", stdin);
    freopen("factor.out", "w", stdout);

    int n;
    while (cin >> n) {
        FOR(i,0,n) cin >> a[i];
        if (n < 2) cout << "YES" << endl;
        else if (n > 2) cout << "NO" << endl;
        else {
            int delta = a[1] * a[1] - 4 * a[0] * a[2];
            if (delta >= 0) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
    }
}
