
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

#define _(X) ((X) & (-(X)))
int n, M, T;
int a[MN], bit[MN], res[MN];

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u < MN) {
        bit[u] += val;
        u += _(u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> M >> T) {
        FOR(i,1,n) {
            int h, m, s; char c;
            cin >> h >> c >> m >> c >> s;
            a[i] = h * 3600 + m * 60 + s + 1;
        }
        sort(a+1, a+n+1);
        memset(bit, 0, sizeof bit);
        bool can = false;
        FOR(i,1,n) {
            int x = get(a[i]) - get(a[i] - T);
            if (x < M) {
                res[i] = res[i-1] + 1;
                update(a[i], 1);

                if (x == M-1) can = true;
            }
            else {
                res[i] = res[i-1];
                update(a[i-1], -1);
                update(a[i], 1);
            }
        }
        if (!can) cout << "No solution" << endl;
        else {
            cout << res[n] << "\n";
            FOR(i,1,n) cout << res[i] << "\n";
        }
    }
    return 0;
}
