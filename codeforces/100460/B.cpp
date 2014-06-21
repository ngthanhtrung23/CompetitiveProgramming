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
int n;
pair<long long, long long> a[MN];

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i].first;
		FOR(i,1,n) cin >> a[i].second;
		sort(a+1, a+n+1);
		FOR(i,1,n) a[i].second += a[i-1].second;

		bool ok = false;
		FOR(i,1,n) if (a[i].first <= a[i].second) ok = true;
		cout << (ok ? "Redemption" : "Dire victory") << endl;
	}
	return 0;
}
