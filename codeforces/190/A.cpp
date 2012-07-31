//#pragma comment(linker, "/STACK:66777216")
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
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int getMin(int a, int b) {
	b -= min(a, b);
	return a + b;
}

int getMax(int a, int b) {
	int res = a;
	if (b) res += b-1;
	return res;
}

int main() {
	int grow, child;
	while (cin >> grow >> child) {
		if (child && !grow) {
			puts("Impossible");
			continue;
		}
		cout << getMin(grow, child) << ' ' << getMax(grow, child) << endl;
	}
    return 0;
}
