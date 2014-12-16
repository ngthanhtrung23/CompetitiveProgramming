#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

char a[22][22];
int m, n, len;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool attempt(int len, int u, int v) {
    if (len == 0) return true;
    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (uu < 1) uu = m;
        if (vv < 1) vv = n;
        if (uu > m) uu = 1;
        if (vv > n) vv = 1;

        if (a[uu][vv] == '#' || a[uu][vv] == 'x') continue;

        if (a[uu][vv] == '.') {
            a[uu][vv] = 'x';
            bool can = attempt(len-1, uu, vv);
            if (can) return true;
            a[uu][vv] = '.';
        }
        if (a[uu][vv] == 'o') {
            a[uu][vv] = 'x';
            bool can = attempt(len, uu, vv);
            if (can) return true;
            a[uu][vv] = 'o';
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> m >> n >> len;
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        int u, v;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'x') {
            u = i;
            v = j;
        }
        cout << "Case #" << test << ": ";
        if (attempt(len-1, u, v)) cout << "Fits perfectly!";
        else cout << "Oh no, snake's too fat!";
        cout << endl;
    }
    return 0;
}
