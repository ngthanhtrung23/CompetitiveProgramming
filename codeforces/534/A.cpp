
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
    int n;
    while (cin >> n) {
        vector<int> res;
        if (n == 1 || n == 2) res = vector<int> {1};
        else if (n == 3) res = vector<int> {1, 3};
        else {
            FORD(i,n,1) if (i % 2 == 1) res.push_back(i);
            FORD(i,n,1) if (i % 2 == 0) res.push_back(i);
        }
        cout << res.size() << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
