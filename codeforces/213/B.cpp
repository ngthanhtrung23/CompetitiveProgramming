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

const int BASE = 1000000007;

int n, a[11];
int f[11][111], c[111][111];

int main() {
	c[0][0] = 1;
	FOR(i,1,100) {
		c[i][0] = 1;
		FOR(j,1,i) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % BASE;
	}
	while (scanf("%d", &n) == 1) {
		REP(i,10) scanf("%d", &a[i]);

		if (n == 1) {
			int sum = 0; REP(i,10) sum += a[i];
			if (sum == 0) {
				puts("10");
			}
			else if (sum == 1) {
				puts("1");
			}
			else {
				puts("0");
			}
			continue;
		}

		int res = 0;
		n--;
		FOR(first,1,9) {
			bool need = false;
			if (a[first]) {
				a[first]--;
				need = true;
			}

			int sum = 0;
			REP(x,10) sum += a[x];

			FOR(k,sum,n) {
				memset(f, 0, sizeof f);
				// f[need to add][already used]
				f[0][0] = 1;
				FOR(cur,0,9) FOR(i,0,k) if (f[cur][i]) {
					FOR(add,a[cur],k-i) {
						f[cur+1][i+add] = (f[cur+1][i+add] + f[cur][i]*(ll)c[k-i][add]) % BASE;
					}
				}
				res = (res + f[10][k]) % BASE;
			}

			if (need) {
				a[first]++;
			}
		}
		cout << res << endl;
	}
    return 0;
}
