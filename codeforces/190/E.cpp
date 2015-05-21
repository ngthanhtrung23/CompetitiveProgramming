
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

const int MN = 500111;
set<int> unvisited;
vector<int> ke[MN];
vector< vector<int> > res;

void bfs(int start) {
    queue<int> qu;
    qu.push(start);
    vector<int> cur;
    unvisited.erase(start);

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        cur.push_back(u);

        vector<int> tmp;
        for(int v : ke[u]) if (unvisited.count(v)) {
            unvisited.erase(v);
            tmp.push_back(v);
        }

        for(int v : unvisited) {
            qu.push(v);
        }
        unvisited.clear();

        for(int v : tmp) {
            unvisited.insert(v);
        }
    }
    res.push_back(cur);
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        unvisited.clear();
        FOR(i,1,n) unvisited.insert(i);

        res.clear();
        while (!unvisited.empty()) {
            int start = *unvisited.begin();
            bfs(start);
        }

        printf("%d\n", res.size());
        for(auto v : res) {
            printf("%d ", v.size());
            for(int x : v) printf("%d ", x);
            puts("");
        }
    }
    return 0;
}

