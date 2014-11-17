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

const int MOD = 1000000007;
int f[211][111];
int n, k, d;

void update(int &x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k >> d) {
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        FOR(sum,0,n-1) FOR(ln,0,k) if (f[sum][ln] > 0) {
            FOR(add,1,k)
                update(f[sum+add][max(add,ln)], f[sum][ln]);
        }
        int res = 0;
        FOR(ln,d,k) update(res, f[n][ln]);
        cout << res << endl;
    }
    return 0;
}

