#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;
int h[MN], a[MN], n;

int getSign(int h1, int h2) {
    if (h1 < h2) return +1;
    else return -1;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("pinball.in", "r", stdin);
    freopen("pinball.out", "w", stdout);

    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &h[i]);
        FOR(i,1,n-1) a[i] = getSign(h[i], h[i+1]);

//        PR(a, n-1);

        int res = 0;
        a[n] = 0;
        FOR(i,0,n-1) if (a[i] != a[i+1]) ++res;
        printf("%d\n", res);

        int q; scanf("%d", &q);
        while (q--) {
            int u, newh; scanf("%d%d", &u, &newh);
            h[u] = newh;
            if (n == 1) {
                printf("%d\n", 1);
                continue;
            }

            if (u == 1) {
                // only a[u] changes
                if (a[u-1] != a[u]) --res;
                if (a[u+1] != a[u]) --res;

                a[u] = getSign(h[u], h[u+1]);

                if (a[u-1] != a[u]) ++res;
                if (a[u+1] != a[u]) ++res;
            }
            else if (u == n) {
                // only a[u-1] changes
                if (a[u-1] != a[u-2]) --res;
                if (a[u-1] != a[u]) --res;

                a[u-1] = getSign(h[u-1], h[u]);

                if (a[u-1] != a[u-2]) ++res;
                if (a[u-1] != a[u]) ++res;
            }
            else {
                if (a[u-2] != a[u-1]) --res;
                if (a[u-1] != a[u]) --res;
                if (a[u] != a[u+1]) --res;

                a[u-1] = getSign(h[u-1], h[u]);
                a[u] = getSign(h[u], h[u+1]);

                if (a[u-2] != a[u-1]) ++res;
                if (a[u-1] != a[u]) ++res;
                if (a[u] != a[u+1]) ++res;
            }
            printf("%d\n", res);
        }
    }
}
