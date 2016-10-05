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
#define y0 y435346

#define maxn 1005

ll n;
II P[maxn];
vector<int> V;
int test;

void solve(){
	cin >> n;
	V.clear();
	Rep(i, n) {
		cin >> P[i].fi >> P[i].se;
		V.pb(P[i].se);
	}

	sort(P, P + n); sort(all(V));
	int m = n / 2;
	ll res = inf;
	Rep(i, n) for(int j = i; j < n; j++){
		vector<int> temp;
		Rep(k, n) if(P[k].se >= V[i] && P[k].se <= V[j]) temp.pb(P[k].fi);
//		if(i == 1 && j == 2) cout << V[i] << " xxx " << V[j] << temp.size() << endl;
		for(int k = 0; k + m < (int)(temp.size()); k++){
			res = min(res, (V[j] - V[i]) * 1ll * (temp[k + m] - temp[k]));
		}
//		cout << i << " " << j << res << " " << endl;
	}

	cout << res << "\n";
}

int main(){
//	freopen("in.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> test;
	Rep(itest, test) solve();
    return 0;
}
