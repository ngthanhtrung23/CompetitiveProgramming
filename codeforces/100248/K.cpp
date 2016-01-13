#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;
const int INF = 2e9 + 11;
int x[MN], y[MN], n, w[MN];

int best, best_w;
int save[MN], t[MN];

void go(int minx, int maxx, int miny, int maxy) {
    if (maxx < minx) swap(maxx, minx);
    if (maxy < miny) swap(maxy, miny);

    int sum = 0;
    FOR(i,1,n) {
        int u = x[i], v = y[i];

        if (minx <= u && u <= maxx && miny <= v && v <= maxy) {
            t[i] = 0;
        }
        else if (minx <= v && v <= maxx && miny <= u && u <= maxy) {
            sum += w[i];
            t[i] = 1;
        }
        else {
            return ;
        }
    }

    int cur = maxx - minx + maxy - miny;
    if (best > cur || (best == cur && sum < best_w)) {
        best = cur;
        best_w = sum;
        FOR(i,1,n) save[i] = t[i];
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        int min_min = INF, min_max = INF;
        int max_min = -INF, max_max = -INF;
        FOR(i,1,n) {
            scanf("%d%d%d", &x[i], &y[i], &w[i]);
            int mn = min(x[i], y[i]);
            int mx = max(x[i], y[i]);

            min_min = min(min_min, mn);
            min_max = min(min_max, mx);

            max_min = max(max_min, mn);
            max_max = max(max_max, mx);
        }

        best = INF;
        best_w = INF;

        go(min_min, max_min, min_max, max_max);
        go(min_max, max_max, min_min, max_min);

        go(min_min, max_max, min_max, max_min);
        go(min_max, max_min, min_min, max_max);

        printf("%I64d %d\n", best * 2LL, best_w);
        FOR(i,1,n) printf("%d", save[i]); puts("");
    }
}
