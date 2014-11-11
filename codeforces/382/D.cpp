#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int  di[] = {-1,1,0,0};
const int  dj[] = {0,0,-1,1};
const char dc[] = {'^', 'v', '<', '>'};
const int MN = 2011;

int m, n, cur;
char a[MN][MN];
#define next next_
int next[MN*MN], to[MN*MN], head[MN*MN];
int visited[MN*MN], vao[MN*MN], f1[MN*MN];

bool dfs1(int u, int fu) {
    visited[u] = 1;
    for(int p = head[u]; p >= 0; p = next[p]) {
        int v = to[p];
        if (!visited[v]) {
            if (dfs1(v, u)) return true;
        }
        else if (visited[v] == 1) return true;
    }
    visited[u] = 2;
    return false;
}

void dfs2(int u) {
    f1[u] = visited[u];
    for(int p = head[u]; p >= 0; p = next[p]) {
        int v = to[p];
        // cout << u << ' ' << v << endl;
        if (!visited[v]) {
            visited[v] = visited[u] + 1;
            dfs2(v);
        }

        if (f1[v] > f1[u]) f1[u] = f1[v];
    }
}

bool hasCycle() {
    memset(visited, 0, sizeof visited);
    FOR(i,1,cur) if (!visited[i]) {
        if (dfs1(i, -1)) return true;
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        cur = 0;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] != '#') {
            ++cur;
        }
        if (cur < 2) {
            cout << 0 << endl;
            continue;
        }
        cur = m * n;
        memset(vao, 0, sizeof vao);
        memset(head, -1, sizeof head);
        memset(next, -1, sizeof next);
        memset(to, 0, sizeof to);

        int nEdges = 0;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] != '#') {
            REP(dir,4) if (dc[dir] == a[i][j]) {
                int ii = i + di[dir], jj = j + dj[dir];
                if (a[ii][jj] != '#') {
                    int u = (i-1)*n+j, v = (ii-1)*n+jj;
                    swap(u, v);

                    next[nEdges] = head[u];
                    to[nEdges] = v;
                    head[u] = nEdges++;

                    vao[v]++;
                }
            }
        }

        if (hasCycle()) {
            cout << -1 << endl;
            continue;
        }

        memset(visited, 0, sizeof visited);
        int ln1 = 0, ln2 = 0, res = 0;
        FOR(i,1,cur) if (!vao[i]) {
            visited[i] = 1;
            dfs2(i);
            res = max(res, f1[i] + f1[i] - 1);
            if (f1[i] > ln1) {
                ln2 = ln1;
                ln1 = f1[i];
            }
            else if (f1[i] > ln2) {
                ln2 = f1[i];
            }
            res = max(res, ln1 + ln2);
        }
        // PR(f1, cur);
        // PR(f2, cur);
        cout << res << endl;
    }
    return 0;
}
