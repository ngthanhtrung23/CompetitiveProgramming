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

const int MN = 100111;

bool isLucky(int n) {
    while (n > 0) {
        if (n % 10 != 4 && n % 10 != 7) return false;
        n /= 10;
    }
    return true;
}

int n;
vector< pair<int,int> > ke[MN];
int down[MN], up[MN];

void dfs1(int u, int fu) {
    down[u] = 0;
    for(auto x : ke[u]) {
        if (x.first == fu) continue;

        dfs1(x.first, u);

        if (x.second == 0) {
            down[u] += down[x.first] + 1;
        }
    }
}

void dfs2(int u, int fu, int back_edge) {
    if (fu > 0 && back_edge == 0) {
        up[u] = (1 + up[fu]) + (down[fu] - down[u] - 1);
    }
    else up[u] = 0;
    for(auto x : ke[u]) {
        if (x.first == fu) continue;

        dfs2(x.first, u, x.second);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            c = isLucky(c);

            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        dfs1(1, -1);
        dfs2(1, -1, 0);

//        PR(down, n);
//        PR(up, n);

        long long res = 0;
        FOR(u,1,n) {
            long long good = n - 1 - down[u] - up[u];
            res += good * (good - 1);
        }
        cout << res << endl;
    }
    return 0;
}

