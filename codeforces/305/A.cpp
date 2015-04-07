
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

int a[111];

int main() {
    int n;
    while (cin >> n) {
        bool has100 = false;
        bool has10 = false;
        bool has01 = false;
        vector<int> res;
        FOR(i,1,n) {
            cin >> a[i];
            if (a[i] == 0) res.push_back(a[i]);
            else if (a[i] == 100) {
                if (!has100) res.push_back(100);
                has100 = true;
            }
            else if (a[i] < 10) {
                if (!has01) res.push_back(a[i]);
                has01 = true;
            }
            else if (a[i] % 10 == 0) {
                if (!has10) res.push_back(a[i]);
                has10 = true;
            }
        }
        if (!has10 && !has01) {
            FOR(i,1,n) if (a[i] != 100 && a[i]) {
                res.push_back(a[i]);
                break;
            }
        }
        cout << res.size() << endl;
        for(auto x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
