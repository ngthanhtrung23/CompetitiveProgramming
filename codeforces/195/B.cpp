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

int n, m, res[100111];

int main() {
    while (cin >> n >> m) {
        int mid = (m + 1) >> 1;
        int cnt = 0;
        while (cnt < n) {
            FOR(diff,0,mid+10) {
                int now = mid - diff;
                if (now > 0 && now <= m) {
                    res[++cnt] = now;
                    if (cnt == n) break;
                }
                if (m % 2 == 1 && !diff) continue;

                now = mid + diff + (m+1)%2;
                if (now > 0 && now <= m) {
                    res[++cnt] = now;
                    if (cnt == n) break;
                }
            }
        }

        FOR(i,1,n) printf("%d\n", res[i]);
    }
    return 0;
}
