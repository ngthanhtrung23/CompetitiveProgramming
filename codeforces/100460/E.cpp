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
const long long oo = 2000111000LL;

#define left left_
#define right right_

long long a[MN], left[MN], right[MN], m;
int n;

long long combine(long long a, long long b) {
	if (a == oo || b == oo) return oo;

	long long t = a * b / __gcd(a, b);
	if (t > oo) return oo;
	else return t;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n >> m) {
		FOR(i,1,n) cin >> a[i];
		left[1] = a[1];
		FOR(i,2,n) left[i] = combine(left[i-1], a[i]);
		right[n] = a[n];
		FORD(i,n-1,1) right[i] = combine(right[i+1], a[i]);

		// PR(left, n);
		// PR(right, n);

		FOR(i,1,n) {
			long long cur;
			if (i == 1) cur = right[2];
			else if (i == n) cur = left[n-1];
			else cur = combine(left[i-1], right[i+1]);

			if (cur == oo) puts("Never");
			else if (cur % a[i] == 0) puts("Never");
			else {
				long long k = m / cur;
				long long x = -m + cur * k;
				while (x < 0) x += cur;
				while (x - cur >= 0) x -= cur;

				if ((m + x) % a[i] == 0) x += cur;
				printf("%d\n", (int) x);
			}
		}
	}
	return 0;
}
