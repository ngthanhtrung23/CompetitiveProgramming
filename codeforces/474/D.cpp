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

const int MN = 200111;
const int MOD = 1000000007;

int f[MN];

void update(int &x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    int ntest, k;
    while (cin >> ntest >> k) {
        memset(f, 0, sizeof f);
        f[0] = 1;
        FOR(i,0,100000) if (f[i]) {
            update(f[i+1], f[i]);
            update(f[i+k], f[i]);
        }

        FOR(i,1,100000) {
            update(f[i], f[i-1]);
        }

        while (ntest--) {
            int l, r; cin >> l >> r;
            cout << (f[r] - f[l-1] + MOD) % MOD << "\n";
        }
    }
    return 0;
}
