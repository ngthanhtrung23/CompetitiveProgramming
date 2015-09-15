
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int n, a[22];

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int f[TWO(15)], res;

void update(int& x, int val) {
    x = max(x, val);
    res = max(res, val);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        REP(i,n) cin >> a[i];
        memset(f, -1, sizeof f);
        sort(a, a+n);

        res = 0;
        f[0] = 0;
        REP(mask,TWO(n)) if (f[mask] >= 0) {
            REP(i,n) if (!CONTAIN(mask,i))
                FOR(j,i+1,n-1) if (!CONTAIN(mask,j))
                    FOR(k,j+1,n-1) if (!CONTAIN(mask,k) && a[k] < a[i] + a[j]) {
                        update(f[mask | TWO(i) | TWO(j) | TWO(k)], f[mask] + 1);
                    }
        }
        cout << res << endl;
    }
}

