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
const int MN = 200111;

#define left left_
#define right right_
int n, k, a[MN], left[MN], right[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];

        FOR(i,1,n) a[i] += a[i-1];
        if (k + k >= n) {
            cout << a[n] << endl;
            continue;
        }

        memset(left, 0, sizeof left);
        memset(right, 0, sizeof right);

        FOR(i,k,n) left[i] = max(a[i] - a[i-k], left[i-1]);
        FORD(i,n-k+1,1) right[i] = max(a[i+k-1] - a[i-1], right[i+1]);

        int res = left[n];
        FOR(i,1,n) res = max(res, left[i] + right[i+1]);
        cout << res << endl;
    }
    return 0;
}
