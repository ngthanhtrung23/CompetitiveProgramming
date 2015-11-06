
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, m;
int bestTime[111], bestBet[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) bestTime[i] = 1000111000, bestBet[i] = 0;

        FOR(i,1,m) {
            int l, r, t, c; cin >> l >> r >> t >> c;
            FOR(x,l,r)
                if (t < bestTime[x]) {
                    bestTime[x] = t;
                    bestBet[x] = c;
                }
        }

        int res = 0;
        FOR(i,1,n) res += bestBet[i];
        cout << res << endl;
    }
}
