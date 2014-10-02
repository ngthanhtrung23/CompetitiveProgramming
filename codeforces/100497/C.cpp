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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 611;
int a[MN][MN], n;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

struct Node {
    int u, v, lastdir, len, diff, startu, startv;
};
int d[MN][MN][4];
queue<Node> qu;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int mid = n+1;
        n = n * 2 + 1;

        while (!qu.empty()) qu.pop();
        memset(d, -1, sizeof d);

        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];

            if (i == 1 || j == 1 || i == n || j == n) {
                Node cur;
                cur.u = i; cur.v = j; cur.lastdir = 0;
                cur.startu = i; cur.startv = j;

                cur.len = 0;
                cur.diff = 0;

                qu.push(cur);
                d[i][j][0] = 0;
            }
        }

        bool ok = false;
        while (!qu.empty()) {
            Node cur = qu.front(); qu.pop();

            if (cur.u == mid && cur.v == mid) {
                cout << cur.len << endl;
                cout << cur.startu << ' ' << cur.startv << endl;
                ok = true;
                break;
            }

            REP(dir,4) {
                int uu = cur.u + di[dir], vv = cur.v + dj[dir];
                if (uu < 1 || vv < 1 || uu > n || vv > n) continue;

                int cur_diff = a[uu][vv] - a[cur.u][cur.v];
                if (cur_diff < cur.diff) continue;

                Node next;
                next.u = uu; next.v = vv;
                next.lastdir = dir;
                next.startu = cur.startu; next.startv = cur.startv;
                next.len = cur.len + 1;
                next.diff = cur_diff;

                if (d[uu][vv][dir] < 0) {
                    qu.push(next);
                    d[uu][vv][dir] = next.len;
                }
            }
        }
        if (!ok) cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
