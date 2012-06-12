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

int n, next[MN][30], cur[30], x[MN];
char a[MN];

int main() {
    while (gets(a)) {
        int n = strlen(a);
        FOR(i,1,n) x[i] = a[i-1] - 'a';
        REP(t,30) cur[t] = n+1;

        FOR(i,1,n) REP(t,30) next[i][t] = n+1;

        FORD(i,n,1) {
            cur[x[i]] = i;
            REP(t,30) next[i][t] = cur[t];
        }

        int i = 1;
        while (i <= n) {
            FORD(t,29,0) if (next[i][t] <= n) {
                putchar(t+'a');
                i = next[i][t] + 1;
                break;
            }
        }
        puts("");
        break;
    }
    return 0;
}
