#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i,s,e) for (int i=(s); i<(e); i++)
#define FOE(i,s,e) for (int i=(s); i<=(e); i++)
#define FOD(i,s,e) for (int i=(s)-1; i>=(e); i--)
#define CLR(a,x) memset(a, x, sizeof(a))
#define EXP(i,l) for (int i=(l); i; i=qn[i])
#define LLD long long
#define N 5300
using namespace std;

int n, m, s, x, na, nb, mx, st, ed;
int v[N], q[N], G[N][N], C[N][N];
LLD ways[N];
LLD MOD = 1000000007;

int Enc(int a, int b, int c){
	int r = c * 2601 + a * 51 + b;
	mx = max(mx, r);
	return r;
}

int main(){
	scanf("%d%d", &n, &m);
	FOR(i,0,n){
		scanf("%d", &x);
		if (x == 50) ++na;
		else ++nb;
	}

	FOE(i,0,n){
		C[i][0] = C[i][i] = 1;
		FOE(j,1,i) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
	}
	
	FOE(i,0,na) FOE(j,0,nb){
		FOE(ii,0,i) FOE(jj,0,j){
			s = ii * 50 + jj * 100;
			if (s == 0 || s > m) continue;
			G[Enc(i, j, 0)][Enc(i-ii, j-jj, 1)] = (C[i][ii] * 1LL * C[j][jj]) % MOD;
		}
		
		FOE(ii,0,na-i) FOE(jj,0,nb-j){
			s = ii * 50 + jj * 100;
			if (s == 0 || s > m) continue;
			G[Enc(i, j, 1)][Enc(i+ii, j+jj, 0)] = (C[na-i][ii] * 1LL * C[nb-j][jj]) % MOD;
		}
	}

	st = Enc(na, nb, 0);
	ed = Enc(0, 0, 1);
	CLR(v, -1);
	v[st] = 0, q[0] = st, ways[st] = 1;
	for (int i=0, j=0; j>=i; i++){
		FOE(k,0,mx) if (G[q[i]][k] > 0){
			if (v[k] == -1){
				v[k] = v[q[i]] + 1;
				q[++j] = k;
			}
			if (v[k] == v[q[i]] + 1){
				ways[k] = (ways[k] + ways[q[i]] * (LLD)G[q[i]][k]) % MOD;
			}
		}
	}
	
	printf("%d\n%I64d\n", v[ed], ways[ed]);
	return 0;
}