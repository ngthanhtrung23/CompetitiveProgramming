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
const int MAXN = 2<<20;
const int P = 1e6+3;

int inv[MAXN];
int fac[MAXN], fac1[MAXN];

int C(int n, int m){
	return (ll)fac[n] * fac1[m] % P * fac1[n-m] % P;
}

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int n, m;
	int i, j, k;
	scanf("%d%d", &n, &m);
	inv[1] = 1;
	for(i = 2; i <= n+m; i++)
		inv[i] = (ll)inv[P%i] * (P-P/i) % P;
	fac[0] = fac1[0] = 1;
	for(i = 1; i <= n+m; i++){
		fac[i] = (ll)fac[i-1] * i % P;
		fac1[i] = (ll)fac1[i-1] * inv[i] % P;
	}
	ll ans = 0;
	for(i = 1; i <= n; i++){
		ans += C(i+m-1, m-1);
	}
	ans %= P;
	cout<<ans<<endl;
	return 0;
}
