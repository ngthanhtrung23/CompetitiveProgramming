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

const int MN = 100111;

struct Robot {
	int c, f, l;
} a[3][MN], cur;

long long sum[3][MN], sl[3][MN];

bool operator < (const Robot &a, const Robot &b) {
	return a.f < b.f;
}

int k, n[3], d, S;

int canLift(long long space, int k0, int k1) {
	if (space == 0) return 0;
	space += sum[0][k0+1] + sum[2][1];
	int res = sl[0][k0+1] + sl[2][1];
	if (space > k - k0 - k1 - res) space = k - k0 - k1 - res;
	return res + space;
}

int get(int s) {
	int space = 0, res = 0;
	int k1 = 0, need = 0;
	while (k1 < n[1] && need + a[1][k1+1].f <= s) {
		need += a[1][k1+1].f;
		++k1;
	}
	res = k1;

	FOR(i,1,n[0]) {
		need += a[0][i].f;
		while (k1 && need > s) {
			need -= a[1][k1].f;
			--k1;
		}
		if (need > s) break;
		space += a[0][i].c;
		res = max(res, i + k1 + canLift(space, i, k1));
	}
	return min(k, res);
}

void inp() {
	scanf("%d%d%d", &k, &d, &S);
	FOR(i,1,k) {
		scanf("%d%d%d", &cur.c, &cur.f, &cur.l);
		if (cur.l >= d) {
			if (cur.c) a[0][++n[0]] = cur;
			else a[1][++n[1]] = cur;
		}
		else a[2][++n[2]] = cur;
	}
	REP(t,3) {
		sort(a[t]+1, a[t]+n[t]+1);

		FORD(i,n[t],1) {
			sum[t][i] = sum[t][i+1] + max(0, a[t][i].c - 1);
			sl[t][i] = sl[t][i+1];
			if (a[t][i].c) sl[t][i]++;
		}
	}
}

int main() {
	inp();

	int can = get(S);
	printf("%d ", can);
	int l = 0, r = S, res = S;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (get(mid) >= can) {
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	printf("%d\n", res);
    return 0;
}