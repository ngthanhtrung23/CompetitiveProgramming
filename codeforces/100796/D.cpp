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
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, m, a, b;
char s[511][511];
int f[511][511], color[511][511];

const int oo = 1e9 + 111;
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d%d%d\n", &n, &m, &a, &b) == 4) {
        FOR(i,1,m) scanf("%s\n", &s[i][1]);

        set< pair<int, pair<int,int> > > all;
        FOR(i,1,m) FOR(j,1,n) f[i][j] = oo;
        memset(color, -1, sizeof color);

        if (s[1][1] == '#' || s[m][n] == '#') {
            puts("IMPOSSIBLE");
            continue;
        }

        f[1][1] = 0;
        color[1][1] = 0;
        all.insert(make_pair(0, make_pair(1, 1)));
        bool found = false;
        while (!all.empty()) {
            int l = all.begin()->first;
            int u = all.begin()->second.first;
            int v = all.begin()->second.second;
            all.erase(all.begin());

            if (u == m && v == n) {
                printf("%d\n", f[u][v]);
                found = true;
                break;
            }

            if (l != f[u][v]) continue;
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (uu < 1 || uu > m || vv < 1 || vv > n) continue;
                if (s[uu][vv] == '#') continue;

                color[uu][vv] = 1 - color[u][v];
                int cost = (color[u][v] == 0) ? b : a;
                if (f[uu][vv] > f[u][v] + cost) {
                    f[uu][vv] = f[u][v] + cost;
                    all.insert(make_pair(f[uu][vv], make_pair(uu, vv)));
                }
            }
        }
        if (!found) puts("IMPOSSIBLE");
    }
}