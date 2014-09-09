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

int n, a[2011][2011];
long long sumAdd[6011], sumDiff[6011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(sumAdd, 0, sizeof sumAdd);
        memset(sumDiff, 0, sizeof sumDiff);
        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];
            sumAdd[i+j] += a[i][j];
            sumDiff[i-j+2000] += a[i][j];
        }

        int x[2], y[2];
        long long best[2];
        best[0] = best[1] = -1;

        FOR(i,1,n) FOR(j,1,n) {
            int t = (i + j) % 2;
            long long cur = sumAdd[i+j] + sumDiff[i-j+2000] - a[i][j];

            if (cur > best[t]) {
                best[t] = cur;
                x[t] = i;
                y[t] = j;
            }
        }

        cout << best[0] + best[1] << endl;
        cout << x[0] << ' ' << y[0] << ' ' << x[1] << ' ' << y[1] << endl;
    }
    return 0;
}

