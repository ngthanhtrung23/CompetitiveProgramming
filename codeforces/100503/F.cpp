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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1000111;
int n, a[MN], it[MN * 4], f[MN], tr[MN];

int better(int u, int v) {
    if (f[u] > f[v]) return u;
    else return v;
}

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

int get(int i, int l, int r, int u, int v) {
    if (u > v) return 0;
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return better(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
}

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = better(it[i], val);
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);

    it[i] = better(it[CT(i)], it[CP(i)]);
}

void trace(int u) {
    if (!u) return ;
    trace(tr[u]);
    cout << a[u] - 1 << ' ';
}

const int inf = 1000000 + 1;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
            ++a[i];
        }
        memset(it, 0, sizeof it);

        int res = 0, save = 0;
        FOR(i,1,n) {
            int u = get(1, 1, inf, 1, a[i] - 2);
            int v = get(1, 1, inf, a[i] + 2, inf);
            int w = get(1, 1, inf, a[i], a[i]);

            tr[i] = better(u, better(v, w));
            f[i] = f[tr[i]] + 1;

            if (f[i] > res) {
                res = f[i];
                save = i;
            }

            update(1, 1, inf, a[i], i);
        }

        cout << n - res << endl;
        trace(save);
        cout << endl;
    }
    return 0;
}
