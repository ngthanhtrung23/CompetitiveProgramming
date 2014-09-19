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

const int MN = 1000111;

map<long long, long long> father, h;
map<long long, bool> visited;

#define next(u) ((u % 2) ? (u + u + u + 1) : (u >> 1))

void visit(long long u) {
    visited[u] = true;

    long long v = next(u);
    if (!visited.count(v)) {
        visit(v);
    }
    father[u] = v;
    h[u] = h[v] + 1;
}

int main() {
    ios :: sync_with_stdio(false);
    visited[1] = true;
    h[1] = 0;

    int u, v;
    while (cin >> u >> v && (u || v)) {
        if (!visited.count(u)) visit(u);
        if (!visited.count(v)) visit(v);
        long long x = u, y = v;
        int du = 0, dv = 0;
        while (x != y) {
            int hx = h[x], hy = h[y];
            if (hx >= hy) {
                du += 1;
                x = father[x];
            }
            if (hx <= hy) {
                dv += 1;
                y = father[y];
            }
        }

        printf("%d needs %d steps, %d needs %d steps, they meet at %I64d\n", u, du, v, dv, x);
    }
    return 0;
}
