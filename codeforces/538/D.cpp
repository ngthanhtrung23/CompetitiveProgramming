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

const int OFFSET = 55;

bool can[111][111];
char a[111][111];
int n;

bool check() {
    FOR(i,1,n) FOR(j,1,n) if (a[i][j] == 'x') {
        bool ok = false;
        FOR(u,1,n) FOR(v,1,n) if (a[u][v] == 'o') {
            int di = i - u, dj = j - v;
            if (can[di + OFFSET][dj + OFFSET]) ok = true;
        }

        if (!ok) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        memset(can, true, sizeof can);
        FOR(i,1,n) FOR(j,1,n) if (a[i][j] == 'o')
            FOR(u,1,n) FOR(v,1,n) if (a[u][v] == '.') {
                int dx = u - i, dy = v - j;

                can[dx + OFFSET][dy + OFFSET] = false;
            }

        if (check()) {
            cout << "YES" << endl;
            FOR(di,-(n-1),n-1) {
                FOR(dj,-(n-1),n-1) {
                    if (di == 0 && dj == 0) cout << 'o';
                    else if (can[di + OFFSET][dj + OFFSET]) cout << 'x';
                    else cout << '.';
                }
                cout << '\n';
            }
        }
        else cout << "NO" << endl;
    }
    return 0;
}
