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

const int MN = 100111;

int n, a[MN], f[MN], g[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
    	FOR(i,1,n) cin >> a[i];

    	FOR(i,1,n) {
    		if (i == 1 || a[i] <= a[i-1]) f[i] = 1;
    		else f[i] = f[i-1] + 1;
    	}

    	FORD(i,n,1) {
    		if (i == n || a[i] >= a[i+1]) g[i] = 1;
    		else g[i] = g[i+1] + 1;
    	}

    	// PR(f, n);
    	// PR(g, n);

    	int res = 0;
    	FOR(i,1,n) res = max(res, f[i]);
    	if (res < n) ++res;

    	FOR(i,2,n-1) {
    		if (a[i-1]+1 < a[i+1])
    			res = max(res, f[i-1] + g[i+1] + 1);
    	}

    	if (res > n) res = n;
    	cout << res << endl;
    }
    return 0;
}
