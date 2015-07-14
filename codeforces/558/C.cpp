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
int a[MN];
long long cnt[MN], to[MN], f[MN];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        memset(cnt, 0, sizeof cnt);
        memset(to, 0, sizeof to);
        memset(f, 0, sizeof f);

        FOR(i,1,n) {
            cnt[a[i]]++;
        }
        FORD(i,100000,1) {
            cnt[i] = cnt[i] + cnt[i*2] + cnt[i*2+1];
            to[i]  = to[i*2] + to[i*2+1] + cnt[i*2] + cnt[i*2+1];
        }
        long long res = to[1];
        f[1] = to[1];
        FOR(i,2,100000) {
            int x = i; while (x % 2 == 0) x /= 2;
            if (cnt[x] < n) continue;

            if (cnt[i] == n) f[i] = to[i];
            else {
                f[i] = f[i/2] - cnt[i] + (n - cnt[i]);
            }
            res = min(res, f[i]);
        }
        cout << res << endl;
    }
}
