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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 10111;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point operator - (const Point &a) { return Point(x-a.x, y-a.y); }

    double len() { return sqrt(x*x + y*y); }
} a[MN];

int n;
set< pair<int,int> > edges;
double d[MN];
int save[MN];
bool good[MN];

void update(int u) {
    FOR(v,1,n) {
        if (edges.count(make_pair(u, v))) {
            d[v] = 0;
            save[v] = u;
        }

        double cur = (a[v] - a[u]).len();
        if (cur < d[v]) {
            d[v] = cur;
            save[v] = u;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cin >> n;
    FOR(i,1,n) cin >> a[i].x >> a[i].y;
    int m; cin >> m;
    FOR(i,1,m) {
        int u, v; cin >> u >> v;
        edges.insert(make_pair(u, v));
        edges.insert(make_pair(v, u));
    }

    good[1] = true;
    FOR(i,1,n) d[i] = 1e50;
    update(1);

    FOR(turn,2,n) {
        int best = -1;
        FOR(i,1,n) if (!good[i]) {
            if (best < 0 || d[i] < d[best])
                best = i;
        }

        if (!edges.count(make_pair(best, save[best]))) {
            cout << best << ' ' << save[best] << endl;
        }
        good[best] = true;

        update(best);
    }
    return 0;
}
