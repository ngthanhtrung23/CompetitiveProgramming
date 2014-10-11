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
#define PR1(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
#define TWO(x) (1<<(x))

int n, a[MN], f[20][MN], lg[MN];

void init() {
    FOR(i,0,20)
        if (TWO(i) < MN) lg[TWO(i)] = i;
    FOR(i,1,MN-1)
        if (!lg[i]) lg[i] = lg[i-1];
}

map<int,long long> save;

int get(int l, int r) {
    int t = lg[r - l + 1];
    return __gcd(f[t][l], f[t][r-TWO(t)+1]);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    init();
    while (cin >> n) {
        save.clear();
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) f[0][i] = a[i];

        FOR(x,1,18)
            FOR(i,1,n)
            if (i + TWO(x) - 1 <= n)
                f[x][i] = __gcd(f[x-1][i], f[x-1][i + TWO(x-1)]);

        FOR(i,1,n) {
            int j = i;
            while (j <= n) {
                int cur = get(i, j);
                int l = j, r = n, res = j;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (get(i, mid) == cur) {
                        res = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }

                save[cur] += (res - j + 1);

                j = res + 1;
            }
        }

        int q; cin >> q;
        while (q--) {
            int u; cin >> u;
            cout << save[u] << "\n";
        }
    }
    return 0;
}

