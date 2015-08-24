
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

const int MN = 511;

int m, n;
int L[MN][MN], R[MN][MN], prefR[MN][MN];
int L2R[MN], R2L[MN];
int p[MN];
bool stableMarriage(int t) {
    static int p[511];
    memset( R2L, -1, sizeof( R2L ) );
    memset( L2R, -1, sizeof L2R);
    memset( p, 0, sizeof( p ) );
    // Each man proposes...
    for( int i = 0; i < n; i++ ) {
        int man = i;
        while (man >= 0) {
            // to the next woman on his list in order of decreasing preference,
            // until one of them accepts;
            int wom;
            bool can = false;
            while(1){
                if (p[man] == t) return false;
                wom = L[man][p[man]++];
                if (wom < 0) return false;
                if (prefR[wom][man] >= t) continue;
                if (R2L[wom] < 0 || prefR[wom][man] < prefR[wom][R2L[wom]] ) {
                    can = true;
                    break;
                }
            }
            if (!can) return false;
            // Remember the old husband of wom.
            int hubby = R2L[wom];
            // Marry man and wom.
            R2L[L2R[man] = wom] = man;
            // If a guy was dumped in the process, remarry him now.
            man = hubby;

        }
    }
    REP(i,n) if (L2R[i] < 0) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        m = n;
        REP(i,n) REP(j,n) {
            cin >> L[i][j];
            --L[i][j];
        }
        REP(i,n) REP(j,n) {
            cin >> R[i][j];
            --R[i][j];
            prefR[i][ R[i][j] ] = j;
        }
        int l = 1, r = n, res = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (stableMarriage(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        stableMarriage(res);
        cout << res << endl;
        REP(i,n) cout << L2R[i]+1 << ' '; cout << endl;
    }
}

