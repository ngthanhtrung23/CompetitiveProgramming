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

bool bad[111][1011];
char tmp[100111];
string a[111], b[1011];
int s, q, f[1011][111], g[1011];

const int oo = 1000111000;

int main() {
    ios :: sync_with_stdio(false);
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        scanf("%d\n", &s);
        FOR(i,1,s) {
            gets(tmp);
            a[i] = string(tmp);
        }
        scanf("%d\n", &q);
        FOR(i,1,q) {
            gets(tmp);
            b[i] = string(tmp);
        }

        FOR(i,1,s) FOR(j,1,q) bad[i][j] = (a[i] == b[j]);

        g[1] = oo;
        FOR(i,1,s) {
            f[1][i] = (bad[i][1]) ? oo : 0;
            g[1] = min(g[1], f[1][i]);
        }

        FOR(i,2,q) {
            g[i] = oo;
            FOR(j,1,s) {
                if (bad[j][i]) f[i][j] = oo;
                else {
                    f[i][j] = min(f[i-1][j], g[i-1] + 1);
                }

                g[i] = min(g[i], f[i][j]);
            }
        }
        cout << g[q] << endl;
    }
    return 0;
}
