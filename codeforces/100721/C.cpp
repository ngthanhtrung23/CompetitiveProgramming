
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
using namespace std;

bool mark[55][55];
int n, r;

void solve() {
    int x, y; cin >> x >> y;
    int dx, dy;
    if (x == 0) {
        dx = 1;
        dy = 0;
    }
    else if (x == n+1) {
        dx = -1;
        dy = 0;
    }
    else if (y == 0) {
        dx = 0;
        dy = 1;
    }
    else {
        dx = 0;
        dy = -1;
    }

    REP(turn,10111) {
        x += dx; y += dy;
        if (mark[x][y]) {
            swap(dx, dy);
            dy = -dy;
        }
        if (x == 0 || x == n+1 || y == 0 || y == n+1) {
            cout << x << ' ' << y << endl;
            return ;
        }
    }
    cout << 0 << ' ' << 0 << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> r;
        memset(mark, false, sizeof mark);
        FOR(i,1,r) {
            int x, y; cin >> x >> y; mark[x][y] = true;
        }
        solve();
    }
}
