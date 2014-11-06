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
const int MV = 1000111;
#define next next_
int n, a[MN], next[MV];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        memset(next, 0, sizeof next);

        FOR(i,1,n) next[a[i]] = a[i];
        FOR(i,1,MV-1) if (!next[i]) next[i] = next[i-1];

        int res = 0;
        FOR(i,1,n) if (i == 1 || a[i] > a[i-1]) {
            for(int k = a[i]; k < MV; k += a[i]) {
                int u = next[min(MV-1, k + a[i] - 1)];
                if (u > k) res = max(res, u - k);
            }
        }
        cout << res << endl;
    }
    return 0;
}

