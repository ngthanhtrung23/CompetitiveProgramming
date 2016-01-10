
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

const int MN = 211;

int x[MN], y[MN];
int cx[MN], cy[MN], sx, sy;
int savex, savey, W, H;
int n;

bool check(int L) {
    sx = sy = 0;
    cx[++sx] = 0;
    cy[++sy] = 0;

    cx[++sx] = W - L;
    cy[++sy] = H - L;

    FOR(i,1,n) {
        if (x[i] + L <= W) cx[++sx] = x[i];
        if (y[i] + L <= H) cy[++sy] = y[i];

        if (x[i] >= L) cx[++sx] = x[i] - L;
        if (y[i] >= L) cy[++sy] = y[i] - L;
    }
    sort(cx+1, cx+sx+1);
    sort(cy+1, cy+sy+1);
    sx = unique(cx+1, cx+sx+1) - cx - 1;
    sy = unique(cy+1, cy+sy+1) - cy - 1;

    FOR(i,1,sx) FOR(j,1,sy) {
        int curx = cx[i], cury = cy[j];
        bool can = true;

        FOR(k,1,n) {
            if (curx < x[k] && x[k] < curx + L &&
                    cury < y[k] && y[k] < cury + L) {
                can = false;
                break;
            }
        }

        if (can) {
            savex = curx;
            savey = cury;
            return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("cricket.in", "r", stdin);
    freopen("cricket.out", "w", stdout);
    while (cin >> n >> W >> H) {
        FOR(i,1,n) cin >> x[i] >> y[i];
        int l = 0, r = min(W, H), res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        check(res);
        cout << savex << ' ' << savey << ' ' << res << endl;
    }
}
