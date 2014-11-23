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

const int MN = 1000111;
int n, a[MN], b[MN], to[MN], vao[MN], res[MN], used[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        memset(to, 0, sizeof to);
        memset(vao, 0, sizeof vao);
        memset(used, 0, sizeof used);
        FOR(i,1,n) {
            cin >> a[i] >> b[i];
            if (a[i]) to[a[i]] = i;
            vao[b[i]]++;
        }
        memset(res, 0, sizeof res);
        FOR(i,1,n) if (a[i] == 0) {
            int u = i;
            for(int x = 1; x <= n; x += 2) {
                res[x+1] = b[u];
                u = to[b[u]];
            }
        }
        FOR(i,1,n) if (vao[a[i]] == 0) {
            int u = i;
            for(int x = 1; x <= n; x += 2) {
                if (a[u]) res[x] = a[u];
                if (b[u]) res[x+2] = b[u];
                u = to[b[u]];
            }
        }

        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
