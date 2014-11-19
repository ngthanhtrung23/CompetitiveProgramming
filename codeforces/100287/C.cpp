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

int n, MOD, d, k;

int next(int u) {
    return (u == n-1) ? 0 : (u+1);
}
int prev(int u) {
    return (u == 0) ? (n-1) : (u-1);
}

void add(int &x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

vector<int> get(int k) {
    vector<int> res; res.resize(n);
    REP(i,n) res[i] = 0;
    if (k == 0) {
        res[0] = 1 % MOD;
        return res;
    }

    if (k & 1) {
        vector<int> cur = get(k-1);
        REP(i,n) {
            for(int turn = 0, j = i; turn <= d; ++turn, j = next(j)) {
                add(res[j], cur[i]);
            }
            for(int turn = 1, j = prev(i); turn <= d; ++turn, j = prev(j)) {
                add(res[j], cur[i]);
            }
        }
        return res;
    }
    else {
        vector<int> cur = get(k >> 1);
        REP(i,n) {
            REP(j,n) {
                add(res[j], cur[i] * (long long) cur[(j+n-i) % n] % MOD);
            }
        }
        return res;
    }
}

int main() {
    freopen("cell.in", "r", stdin); freopen("cell.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> MOD >> d >> k) {
        vector<int> start; start.resize(n); REP(i,n) cin >> start[i];
        vector<int> transform = get(k);
        // PR0(transform, transform.size());

        vector<int> res; res.resize(n); REP(i,n) res[i] = 0;

        REP(i,n) {
            REP(j,n) {
                add(res[j], start[i] * (long long) transform[(j+n-i) % n] % MOD);
            }
            // PR0(res, res.size());
        }

        REP(i,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
