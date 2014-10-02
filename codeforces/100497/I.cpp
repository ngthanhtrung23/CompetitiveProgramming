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

const int MN = 300111;
const int oo = 1000111000;

#define x first.first
#define y first.second
#define c second

int f[MN], n, k, tr[MN];
pair< pair<int,int>, int>a[MN];
int bestX[MN], bestY[MN];
int saveX[MN], saveY[MN];

void init() {
    REP(i,MN) {
        f[i] = bestX[i] = bestY[i] = -oo;
    }
    memset(tr, 0, sizeof tr);
}

void update(int i, int val, int prev) {
    if (f[i] < val) {
        f[i] = val;
        tr[i] = prev;

        if (bestX[a[i].x] < f[i]) {
            bestX[a[i].x] = f[i];
            saveX[a[i].x] = i;
        }

        if (bestY[a[i].y] < f[i]) {
            bestY[a[i].y] = f[i];
            saveY[a[i].y] = i;
        }
    }
}

vector< pair<int,int> > res;
void jump(int v) {
    if (tr[v]) jump(tr[v]);
    res.push_back(make_pair(a[v].x, a[v].y));
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        init();
        FOR(i,1,n) cin >> a[i].x >> a[i].y >> a[i].c;

        int x1 = a[1].x, y1 = a[1].y;
        int xn = a[n].x, yn = a[n].y;

        sort(a+1, a+n+1);

        int u = -1;
        FOR(i,1,n) {
            if (a[i].x == x1 && a[i].y == y1) {
                update(i, a[i].c, 0);
                continue;
            }
            if (a[i].x == xn && a[i].y == yn) {
                u = i;
            }
            int fromX = bestX[a[i].x];
            int fromY = bestY[a[i].y];

            if (max(fromX, fromY) < k) continue;

            if (fromX > fromY) {
                update(i, fromX - k + a[i].c, saveX[a[i].x]);
            } else {
                update(i, fromY - k + a[i].c, saveY[a[i].y]);
            }
        }

        // FOR(i,1,n) cout << a[i].x << ' ' << a[i].y << ' ' << a[i].c << "   " << f[i] << endl;

        cout << f[u] << endl;
        res.clear();
        jump(u);

        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i].first << ' ' << res[i].second << endl;
    }
    return 0;
}
