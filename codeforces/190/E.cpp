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

const int MN = 1000111;

int n, m, mark[MN], next[MN], prev[MN], qu[MN];
bool has[MN];
pair<int,int> a[MN];
vector<int> ke[MN], ls[MN];

int main() {
	scanf("%d%d", &n, &m);
	FOR(i,1,n) a[i].S = i;
	FOR(i,1,m) {
		int u, v; scanf("%d%d", &u, &v);
		ke[u].PB(v);
		ke[v].PB(u);
		a[u].F++;
		a[v].F++;
	}
	sort(a+1, a+n+1);
	int res = 0;
	FOR(i,0,n) next[i] = i+1;
	FOR(i,1,n+1) prev[i] = i-1;

	FOR(t,1,n) {
		int i = a[t].S;
		if (mark[i]) continue;
		++res;
		ls[res].PB(i);
		mark[i] = res;

		int first = 1, last = 1;
		qu[1] = i;
		int a = prev[i], b = next[i];
		next[a] = b;
		prev[b] = a;
		while (first <= last) {
			int u = qu[first++];
			REP(x,ke[u].size()) {
				int v = ke[u][x];
				has[v] = true;
			}

			int v = next[0];
			while (v != n+1) {
				if (!has[v] && !mark[v]) {
					ls[res].PB(v);
					mark[v] = res;
					int a = prev[v], b = next[v];
					next[a] = b;
					prev[b] = a;
					qu[++last] = v;
				}
				v = next[v];
			}

			REP(x,ke[u].size()) {
				int v = ke[u][x];
				has[v] = false;
			}
		}
	}
	printf("%d\n", res);
	FOR(i,1,res) {
		printf("%d", ls[i].size());
		REP(x,ls[i].size())
			printf(" %d", ls[i][x]);
		puts("");
	}
    return 0;
}
