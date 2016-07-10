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
const int N = 105;
const int P = 1e6+3;

int a[N][N], b[N][N], trans[N][N];

void mov(int a[N][N], int b[N][N]){
	int i, j;
	FOR(i, 0, N)
		FOR(j, 0, N)
			a[i][j] = b[i][j];
}

void mul(int a[N][N], int b[N][N], int c[N][N]){
	int i, j, k;
	FOR(i, 0, N)
		FOR(j, 0, N)
			a[i][j] = 0;
	FOR(i, 0, N)
		FOR(j, 0, N)
			FOR(k, 0, N)
				a[i][k] = (a[i][k] + (ll)b[i][j] * c[j][k]) % P;
}

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int n, w, h;
	int i, j, k;
	scanf("%d%d%d", &n, &w, &h);
	for(i = 0; i <= w; i++)
		trans[i][0] += 1;
	for(i = 0; i < w; i++)
		trans[i][i+1] += h;
	for(i = 0; i <= w; i++)
		a[i][i] = 1;
	for(i = 30; i >= 0; i--){
		mul(b, a, a);
		if(1<<i & n)
			mul(a, b, trans);
		else
			mov(a, b);
	}
	int ans = 0;
	for(i = 0; i <= w; i++)
		ans = (ans + a[0][i]) % P;
	printf("%d\n", ans);
	return 0;
}
