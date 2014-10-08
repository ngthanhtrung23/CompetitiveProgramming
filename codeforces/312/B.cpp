#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#define FORE(i,c) for (__typeof ((c).begin ()) i = (c).begin (); i != (c).end (); ++(i))
#define FOR(i,a,b) for (int i = (int) (a), _b = (int) (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (int) (a), _b = (int) (b); i >= _b; --i)
#define REP(i, n) for (int i = 0, _n = (int) (n); i < _n; ++i)
#define SZ(n) ((int) (n).size ())
#define REPV(i, n) REP (i, SZ (n))
using namespace std;
typedef pair <int, int> PII;
typedef long long LL;

int main () {
//	freopen ("in", "r", stdin);
	int a, b, c, d; cin >> a >> b >> c >> d;
	double res = 0, cur = 1;
	REP (i, 100000) {
		res += cur * a / b;
		cur = cur * (1 - 1.0 * a / b) * (1 - 1.0 * c / d);
	}
	printf ("%.13lf\n", res);
	return 0;
}