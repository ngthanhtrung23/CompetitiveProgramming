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
const int N = 1000;
const int K = 20;
const int X = 3;
const int P = 1e9+7;

int a[N][N];

R x[K][N];
R y[K][N];
R d[K][K];
int p[K];
int ansp[K];
R f[1<<K][K];
int pre[1<<K][K];

int main(){
#ifdef LOCAL
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int N;
	scanf("%d", &N);
	while(N--){
		int n, m, k;
		int s;
		int i, j;
		scanf("%d%d%d", &n, &m, &k);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf("%d", &a[i][j]);
		s = n/k;
		m = m/X*X;
		memset(x, 0, sizeof x);
		memset(y, 0, sizeof y);
		memset(d, 0, sizeof d);
		for(i = 0; i < k; i++){
			for(j = 0; j < m; j++)
				for(int xx = i*s; xx < i*s+X; xx++)
					x[i][j] += a[xx][j];
			for(j = 0; j < m; j++)
				for(int xx = (i+1)*s-X; xx < (i+1)*s; xx++)
					y[i][j] += a[xx][j];
		}
		for(i = 0; i < k; i++)
			for(j = 0; j < k; j++){
				R t = 0;
				for(int xx = 0; xx < m; xx++){
					t += y[i][xx] - x[j][xx];
					if(xx%X == X-1){
//						if(N == 18){
//							printf("%d %d %d\n", i, j, (int)t);
//						}
						d[i][j] += abs(t);
						t = 0;
					}
				}
			}
//		for(i = 0; i < k; i++, cout<<endl)
//			for(j = 0; j < k; j++)
//				printf("%6d ", (int)d[i][j]);
		for(i = 0; i < 1<<k; i++)
			for(j = 0; j < k; j++)
				f[i][j] = 1e20;
		for(i = 0; i < k; i++)
			f[1<<i][i] = 0;
		for(i = 1; i < 1<<k; i++){
			for(j = 0; j < k; j++)
				if(1<<j & i)
					for(int x = 0; x < k; x++)
						if(1<<x & ~i)
							if(f[i][j] + d[j][x] < f[i | 1<<x][x]){
								f[i | 1<<x][x] = f[i][j] + d[j][x];
								pre[i | 1<<x][x] = j;
							}
		}
		R ans = 1e20;
		for(i = 0; i < k; i++)
			if(f[(1<<k)-1][i] < ans){
				ans = f[(1<<k)-1][i];
				j = i;
			}
		int cnt = k-1;
		i = (1<<k)-1;
		while(i > 0){
			ansp[cnt--] = j;
			int temp = pre[i][j];
			i ^= 1<<j;
			j = temp;
		}
		for(i = 0; i < k; i++)
			p[ansp[i]] = i+1;
		for(i = 0; i < k; i++)
			printf("%d ", p[i]);
		puts("");
	}
	return 0;
}
