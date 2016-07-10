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
const int N = 1<<20;
const int P = 1e9+7;

int a[1000][1000];

R calc(int n, int m){
	R ret = 0;
	int i, j;
	i = n/2-1;
	for(j = 0; j < m; j++)
		ret += abs(a[i][j] - a[i+1][j]);
	return ret;
}

int main(){
#ifdef LOCAL
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int N;
	scanf("%d", &N);
	while(N--){
		int n, m;
		int i, j, k;
		scanf("%d%d", &n, &m);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf("%d", &a[i][j]);
		R a1 = calc(n, m);
		for(i = 0; i < n/2; i++)
			for(j = 0; j < m; j++)
				swap(a[i][j], a[i+n/2][j]);
		R a2 = calc(n ,m);
		if(a2 < a1)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
