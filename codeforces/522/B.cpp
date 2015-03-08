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

const int MN = 200111;

int n, h[MN], w[MN], maxl[MN], maxr[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        int sumw = 0;
        FOR(i,1,n) {
            scanf("%d%d", &w[i], &h[i]);
            sumw += w[i];
        }
        maxl[0] = 0;
        FOR(i,1,n) maxl[i] = max(maxl[i-1], h[i]);
        maxr[n+1] = 0;
        FORD(i,n,1) maxr[i] = max(maxr[i+1], h[i]);

        FOR(i,1,n) {
            long long curw = sumw - w[i];
            long long curh = max(maxl[i-1], maxr[i+1]);
            printf("%lld ", curw * curh);
        }
        puts("");
    }
    return 0;
}

