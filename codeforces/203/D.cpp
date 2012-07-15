#include <iomanip>
#include <sstream>
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int main() {
	long double a, b, m, vx, vy, vz, t, x, z;
	cin >> a >> b >> m >> vx >> vy >> vz;
	t = - m / vy;
	x = a/2 + t * vx;
	z = t*vz;

	if (x < 0) x = -x;
	if (z < 0) z = -z;

	while (x > 2*a) x -= 2*a;
	while (z > 2*b) z -= 2*b;

	if (x > a) x = a - (x-a);
	if (z > b) z = b - (z-b);

	cout << (fixed) << setprecision(8) << x << ' ' << z << endl;
    return 0;
}
