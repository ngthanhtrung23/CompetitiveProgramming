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

const int MN = 1000111;

#define dec dec_
int n, a[MN], inc[MN], dec[MN];
long long f[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) {
            if (i == 1) inc[i] = dec[i] = 1;
            else {
                if (a[i] >= a[i-1]) inc[i] = inc[i-1];
                else inc[i] = i;

                if (a[i] <= a[i-1]) dec[i] = dec[i-1];
                else dec[i] = i;
            }
        }

        FOR(i,1,n) {
            f[i] = f[i-1];
            f[i] = max(f[i], f[inc[i] - 1] + abs(a[i] - a[inc[i]]));
            f[i] = max(f[i], f[dec[i] - 1] + abs(a[i] - a[dec[i]]));
            if (inc[i] < i) f[i] = max(f[i], f[inc[i]] + abs(a[i] - a[inc[i] + 1]));
            if (dec[i] < i) f[i] = max(f[i], f[dec[i]] + abs(a[i] - a[dec[i] + 1]));
        }
        cout << f[n] << endl;
    }
    return 0;
}
