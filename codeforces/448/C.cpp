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

int n, a[5011], f[5011][5011];

int get(int l, int r, int cut) {
    if (l > r) return 0;
    if (f[l][r] >= 0) return f[l][r];
    f[l][r] = r - l + 1;

    int nn = *min_element(a+l, a+r+1);
    int from = l, cur = 0;
    FOR(i,l,r)
        if (a[i] == nn) {
            cur += get(from, i-1, nn);
            from = i + 1;
        }
    cur += get(from, r, nn);
    f[l][r] = min(f[l][r], nn - cut + cur);
    return f[l][r];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        memset(f, -1, sizeof f);
        FOR(i,1,n) cin >> a[i];
        cout << get(1, n, 0) << endl;
    }
    return 0;
}

