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

int sum, limit;
pair<int,int> a[100111];

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> sum >> limit) {
		FOR(i,1,limit) a[i] = make_pair(i&(-i), i);
		sort(a+1, a+limit+1);

		vector<int> res;
		FORD(i,limit,1)
			if (sum >= a[i].first) {
				sum -= a[i].first;
				res.push_back(a[i].second);
			}
		if (sum) {
			cout << -1 << endl;
			continue;
		}
		cout << res.size() << endl;
		REP(i,res.size()) cout << res[i] << ' '; cout << endl;
	}
	return 0;
}
