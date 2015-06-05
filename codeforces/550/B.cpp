
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, l, r, X, a[22];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> l >> r >> X) {
        REP(i,n) cin >> a[i];

        int res = 0;
        REP(mask,TWO(n)) if (__builtin_popcount(mask) >= 2) {
            vector<int> x;
            REP(i,n) if (CONTAIN(mask,i)) x.push_back(a[i]);

            int sum = accumulate(x.begin(), x.end(), 0);
            if (sum < l || sum > r) continue;
            
            if (*max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end()) < X) continue;
            ++res;
        }
        cout << res << endl;
    }
    return 0;
}

