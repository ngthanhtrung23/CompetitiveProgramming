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

const int MN = 1011;
int n, m, k;
bool ke[MN][MN];
int color[MN];

void init() {
    memset(ke, false, sizeof ke);
    memset(color, -1, sizeof color);
}

void dfs(int u) {
    FOR(v,1,n) if (!ke[u][v]) {
        if (color[v] > 0) continue;

        color[v] = color[u];
        dfs(v);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> k) {
        init();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u][v] = ke[v][u] = true;
        }

        int used = 0;
        FOR(i,1,n) if (color[i] <= 0) {
            ++used;
            if (used > k) {
                cout << -1 << endl;
                break;
            }

            color[i] = used;

            dfs(i);
        }
        if (used > k) continue;
        
        bool good = true;
        FOR(i,1,n) FOR(j,i+1,n) {
            if (ke[i][j] && color[i] == color[j]) good = false;
            if (!ke[i][j] && color[i] != color[j]) good = false;
        }
        if (!good) {
            cout << -1 << endl;
            continue;
        }
        FOR(i,1,n) cout << color[i] << ' '; cout << endl;
    }
    return 0;
}

