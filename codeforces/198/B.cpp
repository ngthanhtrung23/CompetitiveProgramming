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

int n, k;
char a[2][100111];
int visited[2][100111];
int qt[200111], qu[200111], first, last;
bool ok;

void go(int t, int u, int now) {
    if (u < 1) return ;
    if (u > n) {
        ok = true;
        return ;
    }
    if (u < now) return ;
    if (a[t][u] == 'X') return ;
    if (visited[t][u]) return ;

    ++last;
    qt[last] = t; qu[last] = u;
    visited[t][u] = now;
}

int main() {
    while (scanf("%d%d\n", &n, &k) == 2) {
        scanf("%s\n", &a[0][1]);
        scanf("%s\n", &a[1][1]);

        first = 1, last = 1;
        memset(visited, false, sizeof visited);
        qt[1] = 0; qu[1] = 1;
        visited[0][1] = 1;

        ok = false;

        while (first <= last) {
            int t = qt[first], u = qu[first]; ++first;
            go(t, u-1, visited[t][u] + 1);
            go(t, u+1, visited[t][u] + 1);
            go(1-t, u+k, visited[t][u] + 1);
            if (ok) break;
        }
        if (ok) puts("YES");
        else puts("NO");
    }
    return 0;
}
