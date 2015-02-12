
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

#define _(X) ((X) & (-(X)))
int bit[MN], a[3][MN], n;

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u <= n) {
        bit[u] += val;
        u += _(u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        REP(turn,2) {
            FOR(i,1,n) {
                cin >> a[turn][i];
                ++a[turn][i];
            }
        }
        REP(turn,2) {
            memset(bit, 0, sizeof bit);
            FOR(i,1,n) {
                int u = a[turn][i];
                a[turn][i] -= get(u) + 1;
                update(u, 1);
            }
//            PR(a[turn], n);
        }

        memset(a[2], 0, sizeof a[2]);
        FORD(i,n,1) {
            a[2][i] += a[0][i] + a[1][i];

            int avail = n - i + 1;
            a[2][i-1] += a[2][i] / avail;
            a[2][i] %= avail;
        }
//        PR(a[2], n);

        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            int l = 1, r = n, res = r;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (mid - get(mid) >= a[2][i] + 1) {
                    res = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }
            a[2][i] = res;
            update(res, 1);
        }
        FOR(i,1,n) cout << a[2][i] - 1 << ' '; cout << endl;
    }
    return 0;
}
