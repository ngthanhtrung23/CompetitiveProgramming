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

long long n, a[22];
map<long long, long long> f;

int get(long long n) {
    if (f.count(n) && f[n] < 0) return 1000111000LL;
    if (f.count(n)) return f[n];
    if (n == 0) return f[n] = 0;
    
    f[n] = -1;
    long long res = 1000111000111000111LL;
    FORD(i,16,1) if (a[i] <= n) {
        if (n / a[i] >= 5)
            res = min(res, (long long) (i+1) + get(a[i+1] - n));
        res = min(res, (n / a[i]) * i + get(n % a[i]));
        break;
    }
    return f[n] = (int) res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    a[1] = 1;
    FOR(i,2,16) a[i] = a[i-1] * 10LL + 1;

    while (cin >> n) cout << get(n) << endl;
    return 0;
}

