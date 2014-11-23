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

const int MN = 1000111;
int n, k, a[MN], pos[MN], need[MN], bit[MN];

#define _(X) ((X) & (-(X)))
void update(int u, int val) {
    while (u <= n) {
        bit[u] += val;
        u += _(u);
    }
}

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        FOR(i,1,n) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        memset(need, false, sizeof need);
        FOR(i,1,k) {
            int b; cin >> b;
            need[b] = true;
        }
        set<int> bad;
        bad.insert(0);
        bad.insert(n+1);

        long long res = 0;
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) update(i, 1);
        FOR(val,1,n) {
            int u = pos[val];

            if (need[val]) {
                bad.insert(u);
                update(u, -1);
            }
            else {
                auto it = bad.upper_bound(u);
                int right = *it;
                --it;
                int left = *it;

                res += get(right-1) - get(left);

                update(u, -1);
            }
        }
        cout << res << endl;
    }
    return 0;
}

