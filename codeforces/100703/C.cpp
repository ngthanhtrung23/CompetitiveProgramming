
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

const int MN = 211;
const int MN2 = MN * MN;
const int INF = 1000111000;

int n, t, sz[MN], c[MN2], a[MN][MN], nc, f[MN][MN2], tri[MN][MN2];
vector<int> jump;

void trace(int i, int j) {
    if (f[i][j] == 0) return ;
    if (!tri[i][j]) {
        trace(i, j+1);
        return ;
    }

    int ii = tri[i][j];
    int cur = c[j];
    while (i < ii) {
        ++i;
        ++cur;
        if (f[i][j] == -INF) cur = c[j+1];
        jump.push_back(cur);
    }
    trace(ii, j+1);
}

void init() {
    nc = 0;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> t) {
        init();
        c[++nc] = 0;
        c[++nc] = INF;
        FOR(i,1,n) {
            cin >> sz[i];
            sz[i] *= 2;
            FOR(j,1,sz[i]) {
                cin >> a[i][j];
                c[++nc] = a[i][j];
            }
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) FOR(j,1,sz[i]) a[i][j] = lower_bound(c+1, c+nc+1, a[i][j]) - c;

        memset(f, 0, sizeof f);
        memset(tri, 0, sizeof tri);
//        PR(c, nc);
        FORD(i,n,1) {
            for(int j = 1; j < sz[i]; j += 2) {
                int u = a[i][j], v = a[i][j+1];
                FOR(x,u,v-1) f[i][x] = -INF;
            }
            FORD(j,nc,1) if (f[i][j] == 0) {
                if (j == nc) f[i][j] = INF;
                else {
                    f[i][j] = max(0, f[i][j+1]) + c[j+1] - c[j];
                    if (i < n) {
                        FOR(to,i+1,min(n,i+c[j+1] - c[j])) {
                            int cur = f[to][j+1] + c[j+1] - c[j];
                            if (cur > f[i][j]) {
                                f[i][j] = cur;
                                tri[i][j] = to;
                            }
                            if (f[to][j] == -INF) break;
                        }
                    }
                }
            }
        }
        FOR(i,1,n) {
//            PR(f[i], nc);
        }

        int res = INF, savei = 1, savej = nc;
        FOR(i,1,n) FOR(j,1,nc) if (f[i][j] >= t) {
            int cur = c[j];
            if (c[j] < res) {
                res = c[j];
                savei = i;
                savej = j;
            }
        }
        cout << res << endl;
        jump.clear();
        trace(savei, savej);
        int cnt = 0;
        for(int x : jump) if (x < res + t) ++cnt;
        cout << savei << ' ' << cnt << endl;
        for(int x : jump) if (x < res + t) cout << x << ' '; cout << endl;
    }
}

