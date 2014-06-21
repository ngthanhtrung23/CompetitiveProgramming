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
#include <sstream>

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

int a[111], n;
vector<long long> result[111];

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,0,n) result[i].clear();
		result[0].push_back(0);

		FOR(i,1,n) {
			cin >> a[i];
			REP(x,result[i-1].size()) {
				long long old = result[i-1][x];
				long long cur = old + a[i];

				stringstream ss; ss << cur;
				string s = ss.str();
				sort(s.begin(), s.end());

				do {
					stringstream ss2(s);
					long long x; ss2 >> x;
					result[i].push_back(x);
				} while (next_permutation(s.begin(), s.end()));
			}
		}
		long long best = 0;
		REP(x,result[n].size())
			best = max(best, result[n][x]);
		cout << best << endl;
	}
	return 0;
}
