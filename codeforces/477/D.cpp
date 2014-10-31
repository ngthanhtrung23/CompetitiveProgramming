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

const int MN = 5011;
const long long MOD = 1000000007LL;

string s;
int longestEqual[MN][MN];
int f[MN][MN], g[MN][MN];

int lowerOrEqual(int i, int j, int x) {
    if (longestEqual[i][j] >= x) return true;
    i = i + longestEqual[i][j], j = j + longestEqual[i][j];
    if (s[i] < s[j]) return true;
    else return false;
}

void update(int i, int j, int u, int v) {
    if (f[u][v] < 0) return ;
    g[i][j] = (g[i][j] + g[u][v]) % MOD;

    if (f[i][j] < 0) {
        f[i][j] = f[u][v] + 1;
    }
    else if (f[i][j] > f[u][v] + 1) {
        f[i][j] = f[u][v] + 1;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        // DEBUG(s);
        memset(longestEqual, 0, sizeof longestEqual);
        int ls = s.length();
        FORD(j,ls-1,0) FORD(i,j-1,0) {
            if (s[i] == s[j]) {
                longestEqual[i][j] = longestEqual[i+1][j+1] + 1;
            } else {
                longestEqual[i][j] = 0;
            }
        }

        memset(f, -1, sizeof f);
        memset(g, 0, sizeof g);
        FOR(i,0,ls-1) {
            FOR(x,1,i+1) {
                if (x == i+1) f[i][x] = 1, g[i][x] = 1;
                else {
                    f[i][x] = f[i][x-1];

                    if (s[i-x+1] == '1') {
                        if (f[i-x][x-1] > 0) update(i, x, i-x, x-1);
                        if (i - x - x + 1 >= 0 && lowerOrEqual(i-x-x+1, i-x+1, x) && g[i-x][x] > 0) {
                            update(i, x, i-x, x);
                            g[i][x] = (g[i][x] - g[i-x][x-1] + MOD) % MOD;
                        }
                    }
                }
            }
            FOR(x,1,ls) {
                if (x >= i+2) f[i][x] = 1;
                g[i][x] = (g[i][x-1] + g[i][x]) % MOD;
            }
        }

        cout << g[ls-1][ls] << endl;
        long long res = 0;
        bool found = false;
        FOR(x,1,ls) if (g[ls-1][x] != g[ls-1][x-1]) {
            long long cur = 0;
            FOR(i,ls-x,ls-1) cur = (cur * 2 + s[i] - '0') % MOD;
            cur = (cur + f[ls-1][x]) % MOD;

            if (!found) {
                res = cur;
                found = true;
                if (x > 20) break;
            }
            else if (x <= 20) {
                res = min(res, cur);
            }
        }
        cout << res << endl;
    }
    return 0;
}
