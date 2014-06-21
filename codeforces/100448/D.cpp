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

int n, a[10111];
int f[2][17000];
const int MOD = 1000000007;

void update(int &x, int val) {
	x += val;
	if (x >= MOD) x -= MOD;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i];
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		FOR(i,0,n-1) {
			int cur = i & 1;
			memset(f[1-cur], 0, sizeof f[1-cur]);
			REP(mask, 1<<14) if (f[cur][mask]) {
				update(f[1-cur][mask], f[cur][mask]);

				update(f[1-cur][mask^a[i+1]], f[cur][mask]);
				update(f[1-cur][mask^a[i+1]], f[cur][mask]);
			}
		}
		cout << f[n%2][0] << endl;
	}
	return 0;
}
