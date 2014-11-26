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

int m, n;
string a[1011];

void solve() {
    vector<int> cur;
    REP(i,m) {
        int u = a[i].find('G');
        int v = a[i].find('S');
        if (u > v) {
            cout << -1 << endl;
            return ;
        }
        cur.push_back(v - u);
    }
    sort(cur.begin(), cur.end());
    cout << unique(cur.begin(), cur.end()) - cur.begin() << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        REP(i,m) cin >> a[i];

        solve();
    }
    return 0;
}
