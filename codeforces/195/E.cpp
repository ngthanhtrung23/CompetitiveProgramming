#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

const int MN = 100111;
const long long BASE = 1000000007;

int n, lab[MN];
long long depth[MN], sum;

int getRoot(int u) {
    if (lab[u] < 0) return u;
    else {
        int x = getRoot(lab[u]);
        depth[u] += depth[lab[u]]; if (depth[u] >= BASE) depth[u] -= BASE;
        return lab[u] = x;
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        sum = 0;
        memset(lab, -1, sizeof lab);
        memset(depth, 0, sizeof depth);
        FOR(i,1,n) {
            int k, v, x, r, need;
            scanf("%d", &k);

            while (k--) {
                scanf("%d%d", &v, &x);
                if (x < 0) x = BASE + x;
                r = getRoot(v);
                need = depth[v] + x; if (need >= BASE) need -= BASE;
                sum = sum + need; if (sum >= BASE) sum -= BASE;

                lab[r] = i;
                depth[r] = need;
            }
            // PR(lab,n);
            // PR(depth, n);
        }
        cout << sum << endl;
    }
    return 0;
}
