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

const int MN = 5011;

long long f[MN][MN], a[MN];
int n, m, k;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> k) {
        FOR(i,1,n) {
            cin >> a[i];
            a[i] += a[i-1];
        }
        memset(f, 0, sizeof f);
        FOR(i,1,k) {
            FOR(j,i*m,n) {
                f[i][j] = max(f[i][j-1], f[i-1][j-m] + a[j] - a[j-m]);
            }
        }
        cout << f[k][n] << endl;
    }
    return 0;
}
