
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
    long long y, k, n;
    while (cin >> y >> k >> n) {
        long long lb = y - y % k;
        while (lb <= y) lb += k;

        bool ok = false;
        for(long long sum = lb; sum <= n; sum += k) {
            ok = true;
            printf("%d ", (int) sum - y);
        }
        if (!ok) puts("-1");
        else puts("");
    }
    return 0;
}
