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

const int MN = 500111;

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
struct Node {
    int cover, sum;
} it[MN * 8];

int n, q1, q2, l;
int x[MN];

void update(int i, int l, int r, int u, int v, int k) {
    if (v < x[l] || x[r] < u) return ;
    if (u <= x[l] && x[r] <= v) {
        it[i].cover += k;
        if (it[i].cover > 0) it[i].sum = r - l + 1;
        else it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
        return ;
    }

    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, v, k);
    update(CP(i), mid+1, r, u, v, k);

    if (it[i].cover > 0) it[i].sum = r - l + 1;
    else it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q1 >> q2 >> l) {
        x[1] = 0;
        FOR(i,2,n) cin >> x[i];
        memset(it, 0, sizeof it);

        FOR(i,1,q1) {
            int u; cin >> u;
            update(1, 1, n, u-l, u+l, +1);
        }
        cout << it[1].sum << "\n";

        FOR(i,1,q2) {
            int u, v; cin >> u >> v;
            update(1, 1, n, u-l, u+l, -1);
            update(1, 1, n, v-l, v+l, +1);

            cout << it[1].sum << "\n";
        }
    }
    return 0;
}
