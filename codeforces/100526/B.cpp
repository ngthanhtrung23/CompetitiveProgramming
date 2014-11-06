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

int n, t;
int f[3611], a[22];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> t;
        REP(i,n) cin >> a[i];

        memset(f, -1, sizeof f);
        f[0] = 0;
        queue<int> qu;
        qu.push(0);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            REP(i,n) {
                int next = u + a[i];
                if (next < 0) next = 0;
                if (next > 3600) next = 3600;

                if (f[next] < 0) {
                    f[next] = f[u] + 1;
                    qu.push(next);
                }
            }
        }
        int savet = t;
        while (f[t] < 0) {
            ++t;
        }
        cout << f[t] << ' ' << t - savet << endl;
    }
    return 0;
}
