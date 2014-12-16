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

int has[2][111][111][111];
int f[2][111][111][111];

const int di[] = {0,-1,1,0,0};
const int dj[] = {0,0,0,-1,1};

void update(int &x, int val) {
    x = max(x, val);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int q; cin >> q;
        memset(has, 0, sizeof has);
        while (q--) {
            int t, x, y; char typ;
            cin >> t >> x >> y >> typ;
            has[(typ == 'u') ? 0 : 1][t][x][y] += 1;
        }
        memset(f, -1, sizeof f);
        FOR(x,0,100) FOR(y,0,100)
            FOR(typ,0,1)
                f[typ][0][x][y] = 0;
        int res[2]; res[0] = res[1] = 0;

        REP(typ,2)
        FOR(t,0,99)
            FOR(x,0,100) FOR(y,0,100)
                if (f[typ][t][x][y] >= 0) {
                    REP(dir,5) {
                        int xx = x + di[dir], yy = y + dj[dir];
                        if (xx < 0 || xx > 100 || yy < 0 || yy > 100) continue;
                        if (has[1-typ][t+1][xx][yy]) continue;

                        update(f[typ][t+1][xx][yy], f[typ][t][x][y] + has[typ][t+1][xx][yy]);
                    }
                }

        REP(typ,2)
        FOR(t,1,100) FOR(x,0,100) FOR(y,0,100) {
            update(res[typ], f[typ][t][x][y]);
        }

        cout << "Case #" << test << ": " << res[0] << ' ' << res[1] << endl;
    }
    return 0;
}
