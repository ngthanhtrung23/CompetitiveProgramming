#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i >= _b; --i)
#define REP(i,a) for(int i = 0, _a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

long long get(long long x) {
    if (x < 1) return 0;
    if (x < 10) return x;

    long long save = x;
    int last = x % 10;
    while (x >= 10) x /= 10;
    int first = x;
    x = save;

    long long res = 8;
    if (last >= first) ++res;
    res += (x - x % 10) / 10;
    return res;
}

int main() {
    long long l, r;
    while (cin >> l >> r) {
        cout << get(r) - get(l-1) << endl;
    }
    return 0;
}
