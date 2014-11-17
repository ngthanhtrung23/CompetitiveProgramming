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

long long f[70][70][2];
string bits;

long long get(long long n, int k) {
    bits = "";
    while (n) {
        bits = ((char) (n % 2 + '0')) + bits;
        n /= 2;
    }

    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    int l = bits.length();
    FOR(i,0,l-1) FOR(one,0,k) FOR(lower,0,1) if (f[i][one][lower]) {
        FOR(cur,'0','1')
            if (lower || (cur <= bits[i])) {
                int newLower = lower;
                if (cur < bits[i]) newLower = 1;

                int newOne = one;
                if (cur == '1') ++newOne;

                f[i+1][newOne][newLower] += f[i][one][lower];
            }
    }
    return f[l][k][0] + f[l][k][1];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    long long m, k;
    while (cin >> m >> k) {
        long long l = 1, r = 1000111000111000111LL, res = r;
        while (l <= r) {
            long long mid = (l + r) >> 1LL;
            if (get(mid * 2, k) - get(mid, k) >= m) {
                r = mid - 1;
                res = mid;
            }
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
