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

const int MN = 100111;
const int oo = 1000111000;
int n, s, l, a[MN], f[MN], far[MN];

int it[MN * 8];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
#define MID ((l + r) >> 1)

void build(int i, int l, int r) {
    if (l == r) {
        it[i] = oo;
        return ;
    }
    build(CT(i), l, MID);
    build(CP(i), MID+1, r);

    it[i] = oo;
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return oo;
    if (u <= l && r <= v) return it[i];

    return min(get(CT(i), l, MID, u, v), get(CP(i), MID+1, r, u, v));
}

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = val;
        return ;
    }
    update(CT(i), l, MID, u, val);
    update(CP(i), MID+1, r, u, val);
    it[i] = min(it[CT(i)], it[CP(i)]);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> s >> l) {
        FOR(i,1,n) cin >> a[i];
        f[0] = 0;
        FOR(i,1,n) f[i] = oo;
        build(1, 1, n);

        int j = 1;
        multiset<int> cur;
        FOR(i,1,n) {
            cur.insert(a[i]);
            while (*cur.rbegin() - *cur.begin() > s) {
                cur.erase(cur.find(a[j]));
                ++j;
            }
            far[i] = j;
        }
        // PR(far, n);

        FOR(i,1,n) {
            int from = far[i], to = i - l + 1;
            if (from > to) continue;

            if (from == 1) f[i] = 1;
            else f[i] = get(1, 1, n, from-1, to-1) + 1;
            update(1, 1, n, i, f[i]);
        }
        if (f[n] >= oo) f[n] = -1;
        cout << f[n] << endl;
    }
    return 0;
}
