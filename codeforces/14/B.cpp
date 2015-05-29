
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

int n, x0;
pair<int,int> a[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> x0) {
        FOR(i,1,n) cin >> a[i].first >> a[i].second;

        int best = 1011;
        FOR(x,0,1000) {
            bool can = true;
            FOR(i,1,n) {
                int u = min(a[i].first, a[i].second), v = max(a[i].first, a[i].second);
                if (v < x || x < u) {
                    can = false;
                    break;
                }
            }
            if (can) best = min(best, abs(x - x0));
        }
        if (best == 1011) best = -1;
        cout << best << endl;
    }
    return 0;
}

