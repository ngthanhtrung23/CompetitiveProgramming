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

int n, a[111];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        
        vector<int> res;
        int cnt = 0, last = 0;
        FOR(i,1,n) {
            if (a[i] < 0) {
                ++cnt;
                if (cnt == 2) {
                    cnt = 0;
                    res.push_back(i - last);
                    last = i;
                }
            }
        }
        if (last < n) {
            if (cnt || res.empty()) res.push_back(n - last);
            else res.back() += n - last;
        }
        cout << res.size() << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
