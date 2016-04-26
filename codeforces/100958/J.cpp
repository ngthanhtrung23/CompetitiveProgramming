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
typedef double ld;
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos(0))
#define linf (1ll << 60)
#define y1 y32432
#define y2 y435346

#define maxn 200005

ld x;

int n, a[maxn], s;
ll f[maxn], mu[maxn];

void add(ll &x, ll y){
	x += y;
	if(x >= mod) x -= mod;
}

ll mm(ll x, ll k){
	if(k == 0) return 1;
	if(k & 1) return mm(x, k - 1) * x % mod;
	ll T = mm(x, k >> 1);
	return T * T % mod;
}

int main(){
//	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    For(i, 1, n) cin >> a[i];
    f[0] = 1;
    cin >> s;
    mu[0] = 0;
    For(i, 1, s) mu[i] = mm(i, n);
    for(int i = 1; i <= n; i++){
    	for(int j = s; j >= a[i]; j--){
    		add(f[j], mod - f[j - a[i]]);
    	}
    }
    ll res = 0;

    for(int i = 0; i <= s; i++) {
//    	cout << i << " " << f[i] << endl;
    	add(res, f[i] * mu[s - i] % mod);
    }
    cout << res << endl;

    return 0;
}
