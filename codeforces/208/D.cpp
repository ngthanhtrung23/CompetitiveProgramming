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

int n;
long long x[55];
long long cnt[10];
long long a, b, c, d, e;

void get(long long &cur, long long x, int v) {
    long long can = cur / x;
    cnt[v] += can;
    cur = cur % x;
}

void solve(long long &cur) {
    get(cur, e, 5);
    get(cur, d, 4);
    get(cur, c, 3);
    get(cur, b, 2);
    get(cur, a, 1);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);

        FOR(i,1,n) cin >> x[i];
        cin >> a >> b >> c >> d >> e;
        long long cur = 0;
        FOR(i,1,n) {
            cur += x[i];
            solve(cur);
        }
        FOR(i,1,5) cout << cnt[i] << ' ';
        cout << endl << cur << endl;
    }
    return 0;
}
