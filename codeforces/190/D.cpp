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

int n, k, a[400111];
map<int,int> m;

int main() {
	while (scanf("%d%d", &n, &k) == 2) {
		FOR(i,1,n) scanf("%d", &a[i]);

		int j = 0;
		long long res = 0;
		int ok = 0;
		FOR(i,1,n) {
			if (i) {
				m[a[i-1]]--;
				if (m[a[i-1]] == k-1) --ok;
			}
			while (!ok && j < n) {
				++j;
				m[a[j]]++;
				if (m[a[j]] >= k) ++ok;
			}
			if (ok) res += n - j + 1;
		}
		cout << res << endl;
	}
    return 0;
}
