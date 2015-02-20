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

map< pair<int,int>,int > t;
pair<int,int> a[100111];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	FOR(i,1,m) {
		scanf("%d%d", &a[i].F, &a[i].S);
		t[a[i]] = i;
	}
	int res = 1000111000;
	FOR(i,1,m) {
		int now = -1;
		bool ok = true;
		FOR(di,-1,1) FOR(dj,-1,1) {
			if (!t.count(MP(a[i].F + di, a[i].S + dj))) {
				ok = false;
				continue;
			}
			now = max(now, t[MP(a[i].F + di, a[i].S + dj)]);
		}
		if (!ok) continue;
		res = min(res, now);
	}
	if (res == 1000111000) res = -1;
	cout << res << endl;
    return 0;
}