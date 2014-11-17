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
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 200111;
struct Query {
    char typ;
    int x, y;
} queries[MN];

int n, cy[MN], sy;
set< pair<int,int> > bit[MN];

#define _(X) ((X) & (-(X)))

void insert(int u, int x) {
    pair<int,int> add = make_pair(x, -cy[u]);
    while (u <= sy) {
        bit[u].insert(add);
        u += _(u);
    }
}

void remove(int u, int x) {
    pair<int,int> add = make_pair(x, -cy[u]);
    while (u <= sy) {
        bit[u].erase(add);
        u += _(u);
    }
}

pair<int,int> get(int u, int x) {
    pair<int,int> res = make_pair(-1, -1);
    while (u > 0) {
        auto it = bit[u].lower_bound(make_pair(x, 0));
        if (it != bit[u].end()) {
            if (res.first < 0) res = *it;
            else res = min(res, *it);
        }
        u -= _(u);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        string tmp;
        FOR(i,1,n) {
            cin >> queries[i].typ >> tmp >> queries[i].x >> queries[i].y;
            if (queries[i].typ == 'f') {
                ++queries[i].x;
                ++queries[i].y;
            }
            queries[i].y = -queries[i].y;
        }
        sy = 0;
        FOR(i,1,n) cy[++sy] = queries[i].y;
        sort(cy+1, cy+sy+1);
        sy = unique(cy+1, cy+sy+1) - cy - 1;
        FOR(i,1,n) queries[i].y = lower_bound(cy+1, cy+sy+1, queries[i].y) - cy;
        
        FOR(i,1,n) {
            if (queries[i].typ == 'a') insert(queries[i].y, queries[i].x);
            else if (queries[i].typ == 'r') remove(queries[i].y, queries[i].x);
            else {
                pair<int,int> res = get(queries[i].y, queries[i].x);
                if (res.first < 0) cout << -1 << "\n";
                else cout << res.first << ' ' << res.second << "\n";
            }
        }
    }
    return 0;
}
