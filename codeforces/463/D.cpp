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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n, k;
int a[7][1011];
int id[7][1011], f[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,k) FOR(j,1,n) {
            cin >> a[i][j];
            id[i][a[i][j]] = j;
        }

        int res = 0;

        FOR(i,1,n) {
            f[i] = 1;
            FOR(j,1,i-1) {
                bool ok = true;
                int u = a[1][i], v = a[1][j];
                FOR(x,2,k)
                    if (id[x][u] < id[x][v]) ok = false;
                if (ok) f[i] = max(f[i], f[j] + 1);
            }
            res = max(res, f[i]);
        }

        cout << res << endl;
    }
    return 0;
}

