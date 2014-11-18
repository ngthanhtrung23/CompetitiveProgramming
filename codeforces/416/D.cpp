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

#define next next_
const int MN = 200111;
int n;
long long a[MN];
int next[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        next[n+1] = n+1;
        FORD(i,n,1) if (a[i] > 0) next[i] = i; else next[i] = next[i+1];

        int i = 1, res = 0;
        while (i <= n) {
            // DEBUG(i);
            ++res;
            int u = next[i];
            if (u == n+1) { // i --> n: all -1
                i = n+1;
                continue;
            }

            int v = next[u+1];
            if (v == n+1) {
                i = n+1;
                continue;
            }

            if ((a[v] - a[u]) % (v - u)) {
                i = v;
                continue;
            }
            long long d = (a[v] - a[u]) / (v - u);
            long long ai = a[u] - d * (u - i);
            if (ai <= 0) {
                i = v;
                continue;
            }

            int x = v + 1;
            while ((a[x-1] + d > 0) && (a[x] == a[x-1] + d || a[x] < 0)) {
                a[x] = a[x-1] + d;
                ++x;
            }
            i = x;
        }
        cout << res << endl;
    }
    return 0;
}
