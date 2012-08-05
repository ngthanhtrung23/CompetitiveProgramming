#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

const int MN = 1000111;

int n, m;
vector<int> ke[MN];
bool visited[MN];
int qu[MN];
bool need;

int bfs(int u) {
    int first = 1, last = 1;
    qu[1] = u;
    visited[u] = true;

    int res = 0;
    if (ke[u].size() % 2 == 1) ++res;
    need = false;

    while (first <= last) {
        int u = qu[first++];
        REP(i,ke[u].size()) {
            need = true;
            int v = ke[u][i];
            if (visited[v]) continue;

            qu[++last] = v;
            visited[v] = true;
            if (ke[v].size() % 2 == 1) ++res;
        }
    }
    return res;
}

bool ok() {
    FOR(i,1,n)
        if (!visited[i] && ke[i].size()) return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    FOR(i,1,m) {
        int u, v; scanf("%d%d", &u, &v);
        ke[u].PB(v); ke[v].PB(u);
    }
    ke[1].PB(1);
    ke[1].PB(1);

    memset(visited, false, sizeof visited);
    int x = bfs(1);
    if (ok()) {
        printf("%d\n", x/2);
        return 0;
    }

    int res = 0;
    memset(visited, false, sizeof visited);
    FOR(i,1,n) if (!visited[i]) {
        int x = bfs(i);
        if (!need) continue;
        if (x == 0) ++res;
        else res += x / 2;
    }
    printf("%d\n", res);
    return 0;
}
