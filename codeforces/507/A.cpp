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
    cout << (fixed) << setprecision(9);
    int n, k;
    while (cin >> n >> k) {
        vector< pair<int,int> > a;
        FOR(i,1,n) {
            int x; cin >> x;
            a.push_back(make_pair(x, i));
        }
        sort(a.begin(), a.end());

        vector<int> res;
        for(auto x : a) {
            if (k >= x.first) {
                res.push_back(x.second);
                k -= x.first;
            }
        }
        cout << res.size() << endl;
        for(auto x : res) cout << x << ' ';
        cout << endl;
    }
    return 0;
}
