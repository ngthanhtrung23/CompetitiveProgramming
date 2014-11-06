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

const int MN = 100111;

int ke[MN][4];
int n, g;
bool hasg;

void visit(int u, int dir) {
    // cout << "Visit: " << u << ' ' << dir << endl;
    if (u == g) hasg = true;
    while (ke[u][dir]) {
        int v = ke[u][dir];
        if (v == g) hasg = true;
        // cout << v << endl;
        ke[u][dir] = 0;

        REP(nextdir,4) if (ke[v][nextdir] == u) {
            dir = (nextdir + 2) % 4;
            ke[v][nextdir] = 0;
            break;
        }
        u = v;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> g;
        FOR(i,1,n) REP(dir,4) cin >> ke[i][dir];

        int cnt = 0;
        FOR(i,1,n) REP(dir,4)
            if (ke[i][dir]) {
                hasg = false;
                visit(i, dir);
                if (!hasg) ++cnt;
            }
        // DEBUG("done");
        cout << cnt << endl;
    }
    return 0;
}
