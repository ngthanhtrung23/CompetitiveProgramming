#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

long long a, b, c;

long long check(long long t0) {
    for(long long t = t0; t <= t0+c; ++t) {
        long long downloaded = t * b;
        long long need = (t - t0) * a;
        if (need > downloaded) return false;
    }
    return true;
}

int main() {
    while (cin >> a >> b >> c) {
        long long l = 0, r = 1000111000, res = r;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (check(mid)) {
                r = mid - 1;
                res = mid;
            }
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
