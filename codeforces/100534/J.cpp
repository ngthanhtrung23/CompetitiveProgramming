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

int n;
struct Alloy {
    int c, in, out;
} a[1500];
bool operator < (const Alloy &a, const Alloy &b) { return a.c < b.c; }
int nAlloy;
int f[1500][1500][2];

void update(int &x, int val) {
    if (x < 0) x = val;
    else x = min(x, val);
}

int main() {
    while (scanf("%d", &n) == 1) {
        nAlloy = 0;
        memset(f, -1, sizeof f);
        FOR(i,1,n) FOR(j,1,n) {
            int x, y; scanf("%d.%d", &x, &y);
            if (i < j) {
                ++nAlloy;
                a[nAlloy].c = x * 1000 + y;
            }
        }
        nAlloy = 0;
        FOR(i,1,n) FOR(j,1,n) {
            int in; scanf("%d", &in);
            if (i < j) {
                ++nAlloy;
                a[nAlloy].in = in;
            }
        }
        nAlloy = 0;
        FOR(i,1,n) FOR(j,1,n) {
            int out; scanf("%d", &out);
            if (i < j) {
                ++nAlloy;
                a[nAlloy].out = out;
            }
        }
        sort(a+1, a+nAlloy+1);
        // FOR(i,1,nAlloy) cout << a[i].c << ' ' << a[i].in << ' ' << a[i].out << endl;

        f[0][0][0] = 0;
        FOR(i,0,nAlloy-1) FOR(j,0,i) FOR(t,0,1)
            if (f[i][j][t] >= 0) {
                // Do not use
                if (t == 0) update(f[i+1][j][1], f[i][j][0]);
                // Use as out
                update(f[i+1][j+1][t], f[i][j][t] + a[i+1].out);
                // Use as in
                if (j > 0) update(f[i+1][j-1][t], f[i][j][t] + a[i+1].in);
            }

        cout << nAlloy / 2 << ' ' << f[nAlloy][0][nAlloy % 2] << endl;
    }
    return 0;
}
