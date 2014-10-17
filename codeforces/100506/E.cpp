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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

long double c[111][111];
int n, k;
char a[11][11];
bool need[11][11];

void fill(int x) {
    if (x < n) {
        int i = x + 1;
        FOR(j,1,n) need[i][j] = true;
    }
    else if (x < 2*n) {
        int j = x - n + 1;
        FOR(i,1,n) need[i][j] = true;
    }
    else if (x == 2*n) {
        FOR(i,1,n) need[i][i] = true;
    }
    else {
        FOR(i,1,n) need[i][n+1-i] = true;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    FOR(i,0,100) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    int test; cin >> test;
    while (test--) {
        cin >> n >> k;
        int num = 0;
        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] == '.') ++num;
        }
        if (k > num) k = num;

        double res = 0;
        REP(mask,TWO(n+n+2)) if (mask) {
            FOR(i,1,n) FOR(j,1,n) need[i][j] = false;
            double cur = 0;
            REP(x,n+n+2)
                if (CONTAIN(mask,x)) {
                    fill(x);
                }

            int sumNeed = 0;
            FOR(i,1,n) FOR(j,1,n) if (need[i][j] && a[i][j] == '.') ++sumNeed;

            if (sumNeed > k) cur = 0;
            else cur = c[num - sumNeed][k - sumNeed] / c[num][k];

            if (__builtin_popcount(mask) & 1) res += cur;
            else res -= cur;
        }
        cout << 100.0 * res << endl;
    }
    return 0;
}
