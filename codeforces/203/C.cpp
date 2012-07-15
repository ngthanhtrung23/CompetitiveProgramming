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

struct Client {
	int x, y, v, ind;
} c[100111];

bool operator < (const Client &a, const Client &b) {
	return a.v < b.v;
}

int d, a, b, n;

int main() {
	scanf("%d%d", &n, &d);
	scanf("%d%d", &a, &b);
	FOR(i,1,n) {
		scanf("%d%d", &c[i].x, &c[i].y);
		c[i].v = c[i].x * a + c[i].y * b;
		c[i].ind = i;
	}
	sort(c+1, c+n+1);
	int res = 0, now = 0;
	FOR(i,1,n) {
		if (c[i].v <= d && now + c[i].v <= d) {
			++res;
			now += c[i].v;
		}
		else break;
	}
	printf("%d\n", res);
	FOR(i,1,res) printf("%d ", c[i].ind); puts("");
    return 0;
}
