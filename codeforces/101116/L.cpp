#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define inf 1000000005
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))
#define mod 1000000007
#define sz(a) ((int)(a).size())

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s);}
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxn 1005

int n, m, a[maxn][maxn], b[maxn][maxn];
II res[maxn * maxn * 7];
int test, size;

bool cannot(int i, int j, int u){
	return i < n && j < m && a[i + 1][j] == u && a[i][j + 1] == u && a[i + 1][j + 1] == u;
}

bool cannot1(int i, int j, int u){
	return i > 1 && j < m && a[i - 1][j] == u && a[i][j + 1] == u && a[i - 1][j + 1] == u;
}

void doi(int i, int j, int u){
	if(a[i][j] == u) return;
	a[i][j] = u;
	res[size++] = mp(i, j);
}

void sol1(){
	For(i, 1, n) For(j, 1, m){
		int u = ((i + j) & 1) ^ 1;
		if(a[i][j] == u) continue;
		if(cannot(i, j, u)){
			doi(i, j + 1, u ^ 1);
		}
		doi(i, j, u);
	}
}

void sol2(){
	For(i, 1, n) For(j, 1, m){
		int u = b[i][j];
		if(a[i][j] == u) continue;
		if(cannot1(i, j, u)){
			doi(i, j + 1, b[i][j + 1]);
		}
		doi(i, j, u);
	}
}

void solve(){
	cin >> n >> m;
	For(i, 1, n) For(j, 1, m) scanf("%d", &a[i][j]);
	For(i, 1, n) For(j, 1, m) scanf("%d", &b[i][j]);
	size = 0;
	sol1();
//	cout << sz(res) << endl;
	sol2();
	printf("%d\n", size);
	Rep(i, size) printf("%d %d\n", res[i].fi, res[i].se);
}

int main(){
//	freopen("in.txt", "r", stdin);
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);

	test = 1;
	Rep(itest, test) solve();
    return 0;
}
