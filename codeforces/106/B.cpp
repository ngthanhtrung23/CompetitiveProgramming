
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

const int MN = 111;

int a[MN], b[MN], c[MN], cost[MN], n;

bool can(int x) {
    FOR(i,1,n)
        if (a[i] > a[x]
                && b[i] > b[x]
                && c[i] > c[x])
            return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i] >> b[i] >> c[i] >> cost[i];

        int res = -1;
        FOR(i,1,n) {
            if (can(i)) {
                if (res < 0 || cost[res] > cost[i]) res = i;
            }
        }
        cout << res << endl;
    }
}
