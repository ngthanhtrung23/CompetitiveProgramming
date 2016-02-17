
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

int k, n;
int used[111][111], cost[111][111];

int f(int x, int yl, int yr) {
    int res = 0;
    FOR(y,yl,yr) {
        res += cost[x][y];
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> k) {
        int mid = k / 2 + k % 2;
        FOR(i,1,k) FOR(j,1,k) {
            used[i][j] = 0;
            cost[i][j] = abs(i - mid) + abs(j - mid);
        }

        while (n--) {
            int need; cin >> need;
            int best = 1e9;
            int savex = -1, saveyl = -1, saveyr = -1;

            FOR(x,1,k) FOR(yl,1,k - need + 1) {
                int yr = yl + need - 1;
                bool ok = true;
                FOR(y,yl,yr) if (used[x][y]) ok = false;
                if (!ok) continue;

                int cur = f(x, yl, yr);
                if (cur < best) {
                    best = cur;
                    savex = x;
                    saveyl = yl;
                    saveyr = yr;
                }
            }
            if (savex < 0) cout << savex << '\n';
            else {
                cout << savex << ' ' << saveyl << ' ' << saveyr << '\n';
                FOR(y,saveyl,saveyr) {
                    used[savex][y] = true;
                }
            }
        }
    }
}
