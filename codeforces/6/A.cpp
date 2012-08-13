#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int a[11];

bool check(int x, int y, int z, bool ok) {
    if (z < x+y) return true;
    if (!ok && z == x+y) return true;
    return false;
}

int main() {
    while (scanf("%d", &a[1]) == 1) {
        FOR(i,2,4) scanf("%d", &a[i]);
        sort(a+1, a+5);

        bool ok = false;
        FOR(i,1,4) FOR(j,i+1,4) FOR(k,j+1,4)
        if (check(a[i], a[j], a[k], true)) {
            ok = true;
        }
        if (ok) {
            puts("TRIANGLE");
            continue;
        }
        ok = false;
        FOR(i,1,4) FOR(j,i+1,4) FOR(k,j+1,4)
        if (check(a[i], a[j], a[k], false)) {
            ok = true;
        }
        if (ok) {
            puts("SEGMENT");
            continue;
        }
        puts("IMPOSSIBLE");
    }
    return 0;
}
