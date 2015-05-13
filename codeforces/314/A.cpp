
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
long long a[MN];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    long long k;
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        long long sum = 0;
        long long cnt = 0;
        FOR(i,1,n) {
            long long d = sum - (cnt) * (n-i) * a[i];
            if (d < k) {
                cout << i << '\n';
            }
            else {
                sum += a[i] * cnt;
                ++cnt;
            }
        }
    }
    return 0;
}

