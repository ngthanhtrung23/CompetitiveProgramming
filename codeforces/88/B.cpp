
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

int m, n, x;
char a[33][33];
bool can[333];

int main() {
    ios :: sync_with_stdio(false); cin.tie(0);
    while (cin >> m >> n >> x) {
        memset(can, false, sizeof can);
        bool hasShift = false;
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == 'S') {
                hasShift = true;
                FOR(u,1,m) FOR(v,1,n)
                    if (a[u][v] != 'S' && sqr(i-u) + sqr(j-v) <= x*x) {
                        can[a[u][v] ^ ' '] = true;
                    }
            }
            else {
                can[a[i][j]] = true;
            }
        }
        int q; cin >> q;
        string s; cin >> s;
        bool good = true;
        int cnt = 0;
        for(char c : s) {
            if (c >= 'a' && c <= 'z') {
                if (!can[c]) {
                    good = false;
                    break;
                }
            }
            else {
                if (!hasShift) {
                    good = false;
                    break;
                }
                if (!can[c]) {
                    if (can[c ^ ' ']) ++cnt;
                    else good = false;
                }
            }
        }
        if (good) cout << cnt << endl;
        else cout << -1 << endl;
    }
    return 0;
}

