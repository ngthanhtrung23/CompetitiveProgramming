
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

const int MN = 100111;
int n, q, cur;
vector<int> ke[MN];
int father[20][MN], h[MN], getIn[MN], getOut[MN];
vector<int> ls[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(father, 0, sizeof father);
}

void dfs(int u) {
    ls[h[u]].push_back(u);
    getIn[u] = ++cur;
    for(int v : ke[u]) {
        h[v] = h[u] + 1;
        dfs(v);
    }
    getOut[u] = ++cur;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        init();
        FOR(i,1,n) {
            scanf("%d", &father[0][i]);
            ke[father[0][i]].push_back(i);
        }
        cur = 0;
        FOR(i,1,n) if (!father[0][i]) {
            h[i] = 1;
            dfs(i);
        }
        FOR(t,1,19) {
            FOR(u,1,n) {
                int v = father[t-1][u];
                if (v) father[t][u] = father[t-1][v];
            }
        }
        int q; scanf("%d", &q);
        while (q--) {
            int u, p; scanf("%d%d", &u, &p);
            int f = u;
            FORD(i,19,0)
                if ((p >> i) & 1) {
                    f = father[i][f];
                }

            if (f == 0) {
                printf("%d ", 0);
            }
            else {
                int x = h[f] + p;

                int l = 0, r = SZ(ls[x])-1; int res = r;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (getIn[ ls[x][mid] ] >= getIn[f]) {
                        res = mid;
                        r = mid - 1;
                    }
                    else l = mid + 1;
                }
                int firstId = res;

                l = 0, r = SZ(ls[x]) - 1, res = 0;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (getOut[ ls[x][mid] ] <= getOut[f]) {
                        res = mid;
                        l = mid + 1;
                    }
                    else r = mid - 1;
                }
                int lastId = res;

                printf("%d ", lastId - firstId);
            }
        }
    }
}

