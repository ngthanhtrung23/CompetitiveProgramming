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
#define PR1(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int nHor, nVer;
string hor, ver;
bool visited[22][22];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
const int dc[] = {'^', 'v', '<', '>'};

bool bfs(int u, int v) {
    queue<int> qu, qv;
    qu.push(u); qv.push(v);

    memset(visited, false, sizeof visited);
    visited[u][v] = true;

    while (!qu.empty()) {
        int u = qu.front(), v = qv.front(); qu.pop(); qv.pop();

        REP(dir,4) if (dc[dir] == hor[u-1] || dc[dir] == ver[v-1]) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > nHor || vv < 1 || vv > nVer) continue;
            if (visited[uu][vv]) continue;

            visited[uu][vv] = true;
            qu.push(uu);
            qv.push(vv);
        }
    }

    FOR(i,1,nHor) FOR(j,1,nVer) if (!visited[i][j]) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nHor >> nVer) {
        cin >> hor >> ver;

        bool ok = true;
        FOR(i,1,nHor) FOR(j,1,nVer)
            if (!bfs(i, j)) 
                ok = false;

        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}

