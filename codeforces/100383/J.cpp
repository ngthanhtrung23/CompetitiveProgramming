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

ll f[maxn];
pair<ll, ll> P[maxn];
int n;

void update(int u){
	for(int i = u; i > 0; i -= i &-i){
		f[i]++;
	}
}

ll get(int u){
	ll res = 0;
	for(int i = u; i < maxn; i += i &-i){
		res += f[i];
	}
	return res;
}

vector<ll> V;

int main(){
//	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    For(i, 1, n) {
    	cin >> P[i].fi >> P[i].se;
    	V.pb(P[i].fi);
    	V.pb(P[i].se);
    }
    sort(all(V));
    For(i, 1, n){
    	P[i].fi = lower_bound(all(V), P[i].fi) - V.begin() + 1;
    	P[i].se = lower_bound(all(V), P[i].se) - V.begin() + 1;
    }

    sort(P + 1, P + n + 1, greater<pair<ll, ll> >() );

    ll num = 0;
    ll res = 1;
    int i = 1;

    while(i <= n){
    	int u = i;
    	while(u < n && P[u + 1].fi == P[i].fi){
    		u++;
    	}
    	ll A = get(P[i].fi + 1) - num;
    	ll B = (u - i + 1);
    	for(int j = 1; j <= min(A, B); j++){
    		res = res * (max(A, B) - j + 1) % mod;
    	}
    	num += min(A, B);
    	for(int j = i; j <= u; j++){
    		update(P[j].se);
    	}
    	i = u + 1;
    }

    cout << res << endl;

    return 0;
}
