#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n;
vector<int> a[55];

int main() {
    ios :: sync_with_stdio(false);
    int v;
    while (cin >> n >> v) {
        vector<int> res; res.clear();
        FOR(i,1,n) {
            a[i].clear();
            int x; cin >> x;
            while (x--) {
                int u; cin >> u;
                a[i].push_back(u);
            }
            sort(a[i].begin(), a[i].end());
            if (a[i][0] < v) res.push_back(i);
        }
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
