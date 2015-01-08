#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define pow pow__
using namespace std;

const int MN = 100111;

string s;
int q, n;
long long pow[MN], h[2][MN], bit[2][MN];

#define _(X) ((X) & (-(X)))
void update(int t, int u, long long val) {
    while (u <= n) {
        bit[t][u] += val;
        u += _(u);
    }
}

long long get(int t, int u) {
    long long res = 0;
    while (u > 0) {
        res += bit[t][u];
        u -= _(u);
    }
    return res;
}

bool equal(int l, int r, int u, int v) {
    long long h1 = get(0, r) - get(0, l-1);
    int p1 = l;
    long long h2 = get(1, v) - get(1, u-1);
    int p2 = n - v + 1;
    if (p1 == p2) return h1 == h2;
    else if (p1 > p2) return h1 == h2 * pow[p1 - p2];
    else return h2 == h1 * pow[p2 - p1];
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    pow[0] = 1;
    FOR(i,1,MN-1) pow[i] = pow[i-1] * 31;
    while (cin >> s >> q) {
        n = s.length();
        s = " " + s;

        memset(h, 0, sizeof h);
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            h[0][i] = (s[i] - 'a') * pow[i];
            h[1][i] = (s[i] - 'a') * pow[n - i + 1];

            update(0, i, h[0][i]);
            update(1, i, h[1][i]);
        }

        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int p; char x; cin >> p >> x;
                update(0, p, -h[0][p]);
                update(1, p, -h[1][p]);

                h[0][p] = (x - 'a') * pow[p];
                h[1][p] = (x - 'a') * pow[n - p + 1];

                update(0, p, h[0][p]);
                update(1, p, h[1][p]);
            }
            else if (typ == 2) {
                int p; cin >> p;
                int l = 1, r = min(p, n - p + 1), res = 1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (equal(p - mid + 1, p, p, p + mid - 1)) {
                        res = mid;
                        l = mid + 1;
                    }
                    else r = mid - 1;
                }
                cout << res + res - 1 << "\n";
            }
            else {
                int p; cin >> p;
                int l = 1, r = min(p, n - p), res = 0;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (equal(p - mid + 1, p, p + 1, p + mid)) {
                        res = mid;
                        l = mid + 1;
                    }
                    else r = mid - 1;
                }
                if (res == 0) cout << "-1\n";
                else cout << res + res << "\n";
            }
        }
    }
    return 0;
}
