
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1011;
int m, n, k;
int a[MN][MN], id[MN][MN];

int lab[MN*MN];
struct DSU {
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

pair<int, pair<int,int> > all[MN * MN];
int can[MN][MN];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

DSU dsu;

void enable(int u, int v) {
    can[u][v] = 1;
    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (can[uu][vv]) {
            dsu.merge(id[uu][vv], id[u][v]);
        }
    }
}

int visited[MN][MN];
int qu[MN * MN], qv[MN * MN], first, last;

void bfs(int u, int v, int need) {
    first = last = 1;
    qu[1] = u; qv[1] = v;
    visited[u][v] = 1;
    if (need == 1) return ;

    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (can[uu][vv] && !visited[uu][vv]) {
                ++last;
                qu[last] = uu;
                qv[last] = vv;

                visited[uu][vv] = 1;

                if (last == need) {
                    return ;
                }
            }
        }
    }
}

#undef int
int main() {
#define int long long
    while (scanf("%lld%lld%lld", &m, &n, &k) == 3) {
        FOR(i,1,m) FOR(j,1,n) scanf("%lld", &a[i][j]);
        int cnt = 0;

        FOR(i,1,m) FOR(j,1,n) {
            id[i][j] = ++cnt;
            all[cnt] = make_pair(-a[i][j], make_pair(i, j));
        }
        sort(all+1, all+cnt+1);

        dsu.init(cnt);

        memset(can, 0, sizeof can);
        bool good = false;
        FOR(i,1,cnt) {
            int u = all[i].second.first, v = all[i].second.second;
            enable(u, v);

            if (k % a[u][v] == 0) {
                int has = -lab[dsu.getRoot(id[u][v])];
                if (has >= k / a[u][v]) {
                    good = true;
                    puts("YES");

                    memset(visited, 0, sizeof visited);
                    bfs(u, v, k / a[u][v]);

                    FOR(i,1,m) {
                        FOR(j,1,n) if (visited[i][j]) printf("%lld ", a[u][v]); else printf("0 ");
                        puts("");
                    }
                    break;
                }
            }
        }
        if (!good) puts("NO");
    }
}
