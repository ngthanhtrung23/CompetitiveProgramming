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

const int MN = 100111;

int n;
char a[MN], res[MN], b[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d\n", &n) == 1 && n) {
        gets(a);
        int lb = 0;
        memset(b, 0, sizeof b);
        memset(res, 0, sizeof res);
        REP(i,strlen(a)) {
            char c = ' ';
            if (a[i] >= 'a' && a[i] <= 'z') c = a[i] ^ ' ';
            else if (a[i] >= 'A' && a[i] <= 'Z') c = a[i];

            if (c != ' ') {
                b[lb++] = c;
            }
        }
        // DEBUG(b);

        int cur = 0, i = 0;
        REP(turn,lb) {
            res[i] = b[turn];
            i += n;
            if (i >= lb) {
                i = ++cur;
            }
        }

        cout << res << endl;
    }
    return 0;
}
