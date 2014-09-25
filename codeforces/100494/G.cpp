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

char a[55][55];
int qu[55*55], qv[55*55];
bool visited[55][55];
int m, n;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        memset(visited,false, sizeof visited);
        int first = 1, last = 0;
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] == 'P') {
                ++last;
                qu[last] = i;
                qv[last] = j;
                visited[i][j] = true;
            }
        }

        while (first <= last) {
            int u = qu[first], v = qv[first]; ++first;

            bool bad = false;
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (a[uu][vv] == 'T') bad = true;
            }

            if (bad) continue;

            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (a[uu][vv] == '#' || visited[uu][vv]) continue;

                ++last; qu[last] = uu; qv[last] = vv;
                visited[uu][vv] = true;
            }
        }

        int res = 0;
        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == 'G' && visited[i][j]) ++res;
        }
        cout << res << endl;
    }
    return 0;
}
