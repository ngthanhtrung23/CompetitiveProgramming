#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 3011;
pair<int,int> a[MN];

int main() {
    ios :: sync_with_stdio(false);
    int n, v;
    while (cin >> n >> v) {
        FOR(i,1,n) cin >> a[i].first >> a[i].second;
        sort(a+1, a+n+1);

        int res = 0;
        FOR(t,1,3001) {
            int cur = 0;
            FOR(i,1,n) if (a[i].first == t || a[i].first+1 == t) {
                int can = min(a[i].second, v - cur);
                cur += can;
                a[i].second -= can;
            }
            res += cur;
        }
        cout << res << endl;
    }
    return 0;
}
