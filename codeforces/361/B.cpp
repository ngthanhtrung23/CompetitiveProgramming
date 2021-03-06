
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
    ios :: sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        if (k == n) cout << -1 << endl;
        else {
            vector<int> res;
            res.push_back(n-k);
            FOR(i,1,n-k-1) res.push_back(i);
            FOR(i,n-k+1,n) res.push_back(i);
            for(int x : res) cout << x << ' '; cout << endl;
        }
    }
    return 0;
}
