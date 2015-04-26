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
    int n;
    while (cin >> n) {
        vector<int> res;

        while (n > 0) {
            int cur = 0;
            for(int p10 = 1000000; p10 >= 1; p10 /= 10) {
                if ((n % (p10*10)) / p10) {
                    cur += p10;
                }
            }
            n -= cur;
            res.push_back(cur);
        }

        cout << res.size() << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
