
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;
int n, a[MN], cnt[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            if (a[i] >= n) continue;

            cnt[a[i]] += 1;
        }
        FOR(i,1,n) cnt[i] += cnt[i-1];

        FORD(res,n,0) {
            if (cnt[max(0, res-1)] >= res) {
                cout << res << endl;
                break;
            }
        }
    }
}
