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

const int MN = 111;

int m, n;
char tmp[MN][MN];
int a[MN][MN], passed[MN][MN], res;

const int di[] = {0, 1, 0, -1};
const int dj[] = {1, 0, -1, 0};

void add(int u, int v) {
    if (u < 1 || u > m || v < 1 || v > n) return ;
    if (!passed[u][v]) res += a[u][v];
    else res += a[u][v] / 2;
    passed[u][v] = true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) {
            cin >> tmp[i][j];
            a[i][j] = tmp[i][j] - '0';
            passed[i][j] = false;
        }

        res = 0;
        int u = 1, v = 1, dir = 0;
        string s; cin >> s;

        REP(i,s.length()) {
            if (s[i] == 'R') dir = (dir + 1) % 4;
            else if (s[i] == 'L') dir = (dir + 3) % 4;
            else {
                int uu = u + di[dir], vv = v + dj[dir];
                if (dir == 0) {
                    add(u, v);
                    add(u-1, v);
                } else if (dir == 1) {
                    add(u, v);
                    add(u, v-1);
                } else if (dir == 2) {
                    add(u, v-1);
                    add(u-1, v-1);
                } else {
                    add(u-1, v-1);
                    add(u-1, v);
                }
                u = uu; v = vv;
            }
        }
        cout << res << endl;
    }
    return 0;
}
