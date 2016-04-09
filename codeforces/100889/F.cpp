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

#define maxn 2005

int test;
ll M = 1000000005;
ll x1, y1, x2, y2, a1, b1, a2, b2;
ll k;

void swapS(ll &x, ll &y){
	ll temp = M - x;
	x = M - y;
	y = temp;
}

ll intersect(ll u1, ll u2, ll v1, ll v2){
	return max(0ll, min(u2, v2) - max(u1, v1));
}

vector<pair<ll, ll> > cal(ll u1, ll u2, ll v1, ll v2){
	ll d = u2 - u1;
	ll T = 0;
	if(u2 < v1){
		T = (v1 - u2 - 1) / d + 1;
	}
	vector<pair<ll, ll> > res;
	res.pb(mp(T, intersect(u1 + T * d, u2 + T * d, v1, v2)));
	res.pb(mp(T + 1, intersect(u1 + (T + 1) * d, u2 + (T + 1) * d, v1, v2)));
	return res;
}

void solve(){
	cin >> x1 >> y1 >> x2 >> y2;
	cin >> a1 >> b1 >> a2 >> b2;
	cin >> k;
	x2 += x1; y2 += y1; a2 += a1; b2 += b1;
	if(x1 > a1){
		swapS(x1, x2);
		swapS(a1, a2);
	}
	if(y1 > b1){
		swapS(y1, y2);
		swapS(b1, b2);
	}
//	cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
//	cout << a1 << " " << a2 << " " << b1 << " " << b2 << endl;
//	cout << "zzzz" << endl;
	vector<pair<ll, ll> > V1 = cal(x1, x2, a1, a2);
	vector<pair<ll, ll> > V2 = cal(y1, y2, b1, b2);

	ll res = 0;
	Rep(i, sz(V1)) Rep(j, sz(V2)){
		ll A = V1[i].fi + V2[j].fi;
		ll B = V1[i].se * V2[j].se;
//		cout << V1[i].se << " " << V2[j].se << endl;
		if(A <= k) res = max(res, B);
	}
	cout << res << endl;
}

int main(){
//	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> test;
    For(itest, 1, test){
    	solve();
    }

    return 0;
}
