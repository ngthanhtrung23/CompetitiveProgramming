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

long long n, k, d;
bool check() {
    long long cur = 1;
    FOR(i,1,d) {
        cur = cur * k;
        if (cur >= n) return true;
    }
    return false;
}

int a[1011][1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k >> d) {
        if (!check()) {
            cout << -1 << endl;
            continue;
        }
        FOR(i,1,n) {
            if (i == 1) {
                FOR(j,1,d) a[j][i] = 1;
            }
            else {
                FOR(j,1,d) a[j][i] = a[j][i-1];
                int rem = 1;
                FORD(j,d,1) {
                    a[j][i] += rem;
                    if (a[j][i] <= k) {
                        rem = 0;
                    } else {
                        a[j][i] = 1;
                        rem = 1;
                    }
                }
            }
        }
        FOR(i,1,d) {
            FOR(j,1,n) cout << a[i][j] << ' ';
            cout << endl;
        }
    }
    return 0;
}
