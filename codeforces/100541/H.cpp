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

int main() {
    int ntest; cin >> ntest;
    assert(0 < ntest && ntest <= 150);
    while (ntest--) {
        long long m, n, l; cin >> m >> n >> l;
        assert(1 <= m && m <= 1000000);
        assert(1 <= n && n <= 1000000);
        assert(1 <= l && l <= sqr(1000000LL));
        l *= 2;
        vector<long long> factors;
        for(long long i = 1; i*i <= l; ++i) if (l % i == 0) {
            factors.push_back(i);
            if (i*i != l) factors.push_back(l/i);
        }
        sort(factors.begin(), factors.end());
        long long res = 1e13;
        REP(iw,factors.size()) {
            long long w = factors[iw];
            REP(ih,factors.size()) if ((l / w) % factors[ih] == 0) {
                long long h = factors[ih];
                if (w * h > res) break;

                long long x = l / w / h + 1 + n - n*h - w;
                if (x >= 0 && x % 2 == 0) {
                    x /= 2;
                    int i = x % n, u = x / n;

                    if (0 <= i && i <= n - w && 0 <= u && u <= m - h) {
                        res = w * h;
                    }
                }
            }
        }
        if (res > m * n) res = -1;
        cout << res << endl;
    }
    return 0;
}
