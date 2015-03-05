
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

int main() {
    ll x, y, m;
    while (cin >> x >> y >> m) {
        if (x >= m || y >= m) cout << 0 << endl;
        else if (x <= 0 && y <= 0) cout << -1 << endl;
        else {
            if (x > y) swap(x, y);
            ll add = 0;
            if (x < 0) {
                add = (-x) / y;
                x = x + y * add;
            }

            bool ok = false;
            REP(turn,1000111) {
                if (x > y) swap(x, y);
                // now x <= y
                ll s = x + y;
                if (s < x) break;

                x = s;
                if (x >= m || y >= m) {
                    cout << add+1+turn << endl;
                    ok = true;
                    break;
                }
            }
            if (!ok) cout << -1 << endl;
        }
    }
    return 0;
}

