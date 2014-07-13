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

char s[1011];
int w[333];
int k;

int main() {
	gets(s);
	cin >> k;
	FOR(c,'a','z') cin >> w[c];

	long long res = 0;
	REP(i,strlen(s)) {
		res += (i+1) * w[s[i]];
	}
	FOR(i,strlen(s),strlen(s)+k-1) {
		res += (i+1) * (*max_element(w+'a', w+'z'+1));
	}
	cout << res << endl;
	return 0;
}
