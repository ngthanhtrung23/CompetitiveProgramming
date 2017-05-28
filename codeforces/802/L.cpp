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
#define sz(a) ((ll)(a).size())

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcnt(s);}
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef double ld;
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxn 500005

ll mu(ll x, ll k){
	if(k == 0) return 1;
	if(k & 1) return mu(x, k - 1) * x % mod;
	ll T = mu(x, k >> 1);
	return T * T % mod;
}

int n;
vector<II> V[maxn];
ll f[maxn], g[maxn], res;

void go(int par, int u){
	if(u && sz(V[u]) == 1) return;

	int num = sz(V[u]);
	ll A = mu(num, mod - 2);
	ll X = 0, Y = 0;
	Rep(i, sz(V[u])){
		int v = V[u][i].fi;
		ll c = V[u][i].se;
		if(v == par) {
			X = (X + A * c) % mod;
			continue;
		}
		go(u, v);
//		if(u == 0) cout << u << " " << v << " " << c << " " << A << endl;
		X = (X + A * (f[v] + c)) % mod;
		Y = (Y + A * g[v]) % mod;
//		if(u == 0) cout << u << " " << v << " " << c << " " << A << " " << X << " " << Y << endl;
	}
	f[u] = X * mu((mod + 1 - Y), mod - 2) % mod;
	g[u] = A * mu((mod + 1 - Y), mod - 2) % mod;
//	cout << u << " " << f[u] << " " << g[u] << " " << X << " " << Y << " " << A << " " << endl;
}

int main()
{
//	freopen("in.txt", "r", stdin);

	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
//	cout << 1 * mu(8, mod - 2) % mod<< endl;
	Rep(run, n - 1){
		int u, v, c;
		cin >> u >> v >> c;
		V[u].pb(mp(v, c));
		V[v].pb(mp(u, c));
	}

	ms(f, 0);
	ms(g, 0);
	go(-1, 0);
	cout << f[0] << endl;

	return 0;
}
