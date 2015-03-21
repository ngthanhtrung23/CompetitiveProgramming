
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
int n, M, T;
int a[MN], bit[MN], res[MN];

#define _(X) ((X) & (-(X)))
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
    while (scanf("%d%d%d", &n, &M, &T) == 3) {
        FOR(i,1,n) {
            int h, m, s; scanf("%d:%d:%d", &h, &m, &s);
            a[i] = h * 3600 + m * 60 + s + 1;
        }
        memset(bit, 0, sizeof bit);
        bool ok = false;
        FOR(i,1,n) {
            int x = a[i] - T + 1;
            if (x < 0) x = 0;

            int has = get(a[i]);
            if (x) has -= get(x-1);

            if (has + 1 >= M) ok = true;

            if (has < M) {
                res[i] = res[i-1] + 1;
                update(a[i], 1);
            }
            else {
                res[i] = res[i-1];
                update(a[i-1], -1);
                update(a[i], 1);
            }
        }

        if (!ok) cout << "No solution" << endl;
        else {
            printf("%d\n", res[n]);
            FOR(i,1,n) printf("%d\n", res[i]);
        }
    }
    return 0;
}
