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
    assert(1 <= ntest && ntest <= 30);
    while (ntest--) {
        long long n; cin >> n;
        assert(1 <= n && n <= sqr(1000000LL));

        long long res = 0;
        for(long long i=1; i <= n; ) {
            long long value = n / i;
            long long last = n / value;
            res += (last - i + 1) * value;
            res %= 1000000LL;
            i = last + 1;
        }
        cout << res << endl;
    }
    return 0;
}
