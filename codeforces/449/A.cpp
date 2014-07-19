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

long long get(long long n, long long m, long long k) {
	if (k > m + n - 2) return -1;

	if (k > n-1) {
		return m / (k - (n-1) + 1);
	} else {
		return m * (n / (k+1));
	}
}

int main() {
	int n, m, k;
	ios :: sync_with_stdio(false);
	while (cin >> n >> m >> k) {
		cout << max(get(n, m, k), get(m, n, k)) << endl;
	}
	return 0;
}
