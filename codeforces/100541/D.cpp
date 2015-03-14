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

long long add[44][100], to[44][100];

int main() {
    REP(t,35) {
        if (t == 0) {
            REP(i,100) {
                add[0][i] = i;
                to[0][i] = (i + i) % 100;
            }
        }
        else {
            REP(i,100) {
                int j = to[t-1][i];
                add[t][i] = add[t-1][i] + add[t-1][j];
                to[t][i] = to[t-1][j];
            }
        }
    }
    int ntest; cin >> ntest;
    assert(0 < ntest && ntest <= 500);
    while (ntest--) {
        long long n, k; cin >> n >> k;
        assert(0 < n && n <= 1000000000);
        assert(0 < k && k <= 1000000000);

        FORD(t,34,0) if (k >= (1LL << (long long) t)) {
            k -= 1LL << (long long) t;
            int cur = n % 100;
            n += add[t][cur];
        }
        cout << n << endl;
    }
    return 0;
}
