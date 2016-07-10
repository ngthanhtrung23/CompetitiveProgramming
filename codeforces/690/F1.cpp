#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
using namespace std;
typedef long long ll;
typedef double R;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define FOR(i, s, t) for(i = (s); i < (t); i++)
#define RFOR(i, s, t) for(i = (s)-1; i >= (t); i--)

const R PI = acos(-1);
const int MAXN = 1<<20;
const int P = 1e9+7;

int deg[MAXN];
vector<int> e[MAXN];

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int n;
	int i, j, k;
	scanf("%d", &n);
	for(i = 01; i < n; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		deg[a]++;
		deg[b]++;
		e[a].pb(b);
		e[b].pb(a);
	}
	ll ans = 0;
	for(i = 1; i <= n; i++)
		ans += (ll)deg[i] * (deg[i]-1) / 2;
	cout<<ans<<endl;
	return 0;
}
