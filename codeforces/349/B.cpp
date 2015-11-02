
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

int has, cost[11];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> has) {
        FOR(i,1,9) cin >> cost[i];
        int best = *min_element(cost+1, cost+10);
        
        int nDigit = has / best;
        if (nDigit == 0) {
            cout << -1 << endl;
            continue;
        }
        FOR(i,1,nDigit) {
            FORD(cur,9,1) {
                if (has - cost[cur] >= (nDigit - i) * best) {
                    has -= cost[cur];
                    cout << cur;
                    break;
                }
            }
        }
        cout << endl;
    }
}
