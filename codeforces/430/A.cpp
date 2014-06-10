#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

pair<int,int> x[111];
int res[111];

int main() {
    ios :: sync_with_stdio(false);
    int m, n;
    while (cin >> n >> m) {
        FOR(i,1,n) {
            cin >> x[i].first;
            x[i].second = i;
        }
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
        }
        sort(x+1, x+n+1);
        FOR(i,1,n) res[x[i].second] = i % 2;
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
