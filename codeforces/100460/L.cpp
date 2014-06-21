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

struct Event {
	vector<int> id;
	int ln;
} events[MN];

bool operator < (const Event &a, const Event &b) {
	return a.ln < b.ln;
}

int rel[MN], nEvent, nPeople;

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> nEvent >> nPeople) {
		memset(rel, 0, sizeof rel);
		FOR(i,1,nEvent) {
			int k;
			cin >> k >> events[i].ln;
			events[i].id.resize(k);
			REP(t,k) cin >> events[i].id[t];
		}
		sort(events+1, events+nEvent+1);

		bool res = true;
		FOR(i,1,nEvent) {
			bool can = false;

			REP(t,events[i].id.size()) {
				int u = events[i].id[t];
				if (!rel[u]) {
					can = true;
					rel[u] = events[i].ln;
				}
				else if (rel[u] == events[i].ln) can = true;
			}

			if (!can) res = false;
		}
		if (!res) puts("Poor memory");
		else {
			puts("Good memory");
			FOR(i,1,nPeople) printf("%d ", rel[i] ? rel[i] : 1);
			puts("");
		}
	}
	return 0;
}
