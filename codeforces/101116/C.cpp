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

#define maxn 105

ld f[105][maxn * maxn];
ld p[maxn];
int n, s, k, d;
int test;

void solve(){
	cin >> n >> s >> k >> d;
	For(i, 0, n) cin >> p[i];

	ms(f, 0);
	cout << fixed << setprecision(9);
//	cout << n << " " << s << " " << k << " " << d << endl;
	for(int i = 0; i <= d * n; i++) f[n][i] = 0;
//	cout << n << " " << s << " " << k << " " << d << endl;
	for(int i = n - 1; i >= s; i--) {
//		cout << i << endl;

		ld a[12][12]; ms(a, 0);
		a[0][0] = 1;
		for(int j = 0; j < k; j++) for(int t = 0; t <= j; t++){
			int u = min(n, i + t);
			a[j + 1][t + 1] += (n - u) * ld(1.0) / n * a[j][t];
			a[j + 1][t] += u * ld(1.0) / n * a[j][t];
		}

		for(int j = n * d; j >= 0; j--) {
			if(i + j / d >= n){
				f[i][j] = 0; continue;
			}
			f[i][j] = ld(1) / p[i];
			for(int t = k; t >= 0; t--) {
//			if(i == 2 && j == 0) cout << f[2][0] << endl;
				ld P = a[k][t];
				int ii = min(n, i + t);
				int jj = min(k - t + j, n * d);
				f[i][j] += P * f[ii][jj];
			}
			if(j >= d) f[i][j] = min(f[i][j], f[i + 1][j - d]);
		}
	}

	cout << f[s][0] << "\n";

}

int main(){
//	freopen("in.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> test;
	Rep(itest, test) solve();
    return 0;
}
