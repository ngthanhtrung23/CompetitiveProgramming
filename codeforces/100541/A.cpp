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

int n, a[111], nn[111];



int main() {
    int ntest; cin >> ntest;
    assert(1 <= ntest && ntest <= 10);
    while (ntest--) {
        long long w;
        cin >> n >> w;
        assert(0 <= n && n <= 100);
        assert(0 < w && w <= 1000000);
        FOR(i,1,n) {
            cin >> a[i];
            assert(0 < a[i] && a[i] <= 1000);
            if (i == 1) nn[i] = a[i];
            else nn[i] = min(nn[i-1], a[i]);
        }
        long long res = w;
        FOR(i,2,n) {
            res = max(res, (w / nn[i-1] * a[i]) + w % nn[i-1]);
        }
        cout << res - w << endl;
    }
    return 0;
}
