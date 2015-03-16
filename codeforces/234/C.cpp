
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

const int MN = 100111;
int npos[MN], nneg[MN], a[MN];

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,n) npos[i] = npos[i-1] + (a[i] >= 0);
        nneg[n+1] = 0;
        FORD(i,n,1) nneg[i] = nneg[i+1] + (a[i] <= 0);

        int res = n;
        FOR(k,1,n-1) res = min(res, npos[k] + nneg[k+1]);
        cout << res << endl;
    }
    return 0;
}
