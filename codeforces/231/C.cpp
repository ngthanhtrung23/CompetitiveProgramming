
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
int n, k;
long long a[MN], sum[MN];

int main() {
    while (scanf("%d%d\n", &n, &k) == 2) {
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            a[i] = x;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) sum[i] = sum[i-1] + a[i];
        int best = 0, save = -1000111000;

        FOR(i,1,n) {
            int l = 1, r = i, res = i;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (a[i] * (i - mid + 1LL) - (sum[i] - sum[mid-1]) <= k) {
                    res = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }

            int len = i - res + 1;
            if (len > best) {
                best = len;
                save = a[i];
            }
        }

        printf("%d %d\n", best, save);
    }
    return 0;
}
