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

int cnt[11][11], m, n, k;
int res;
char a[22][22];

void attempt(int i, int j) {
    if (i > m) {
        ++res;
        if (res == 1) {
            FOR(i,1,m) { FOR(j,1,n) cout << a[i][j]; cout << endl; }
        }
        return ;
    }

    int ii = i, jj = j + 1;
    if (jj > n) {
        jj = 1;
        ++ii;
    }

    if (a[i][j] >= '0' && a[i][j] <= '9') {
        if (a[i][j+1] >= '0' && a[i][j+1] <= '9') {
            int u = a[i][j] - '0', v = a[i][j+1] - '0';

            if (cnt[u][v]) {
                char save1 = a[i][j], save2 = a[i][j+1];

                a[i][j] = '['; a[i][j+1] = ']';
                --cnt[u][v];
                --cnt[v][u];

                attempt(ii, jj);

                ++cnt[u][v];
                ++cnt[v][u];
                a[i][j] = save1;
                a[i][j+1] = save2;
            }
        }

        if (a[i+1][j] >= '0' && a[i+1][j] <= '9') {
            int u = a[i][j] - '0', v = a[i+1][j] - '0';

            if (cnt[u][v]) {
                char save1 = a[i][j], save2 = a[i+1][j];

                a[i][j] = 'n';
                a[i+1][j] = 'u';
                --cnt[u][v];
                --cnt[v][u];

                attempt(ii, jj);

                a[i][j] = save1;
                a[i+1][j] = save2;
                ++cnt[u][v];
                ++cnt[v][u];
            }
        }
    } else {
        attempt(ii, jj);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> k && m) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,k) {
            int u, v;
            cin >> u >> v;
            cnt[u][v]++;
            cnt[v][u]++;
        }
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        // FOR(i,1,m) { FOR(j,1,n) cout << a[i][j]; cout << endl; }

        res = 0;
        attempt(1, 1);
        if (!res) cout << "impossible" << endl << endl;
        else cout << res - 1 << endl;
        cout << endl;
    }
    return 0;
}
