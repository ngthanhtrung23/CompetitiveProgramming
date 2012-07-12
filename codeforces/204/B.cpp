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

map<int,int> cur, add;

int main() {
    int n; scanf("%d", &n);
    FOR(i,1,n) {
        int u, v; scanf("%d%d", &u, &v);
        cur[u]++;
        if (u != v) add[v]++;
    }
    int need = n / 2 + n % 2;
    int res = n + 1;
    for(map<int,int> :: iterator it = cur.begin(); it != cur.end(); it++) {
        int x = it->F;
        if (cur[x] + add[x] >= need) {
            res = min(res, need - cur[x]);
        }
    }
    for(map<int,int> :: iterator it = add.begin(); it != add.end(); it++) {
        int x = it->F;
        if (cur[x] + add[x] >= need) {
            res = min(res, need - cur[x]);
        }
    }
    if (res < 0) res = 0;
    if (res > n) res = -1;
    cout << res << endl;
    return 0;
}
