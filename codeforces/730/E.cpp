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
template<class T> int cntbit(T s) { return __builtin_popcount(s);}
#define Rep(i,n) for(ll i = 0; i < (n); ++i)
#define Repd(i,n) for(ll i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(ll i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(ll i = (a); i >= (b); --i)

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

int n, a[maxn], b[maxn];
vector<II> V[2];

int main()
{
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    For(i, 1, n) {
    	cin >> a[i] >> b[i];
    	if(b[i] >= 0){
    		V[0].pb(mp(a[i], -i));
    	} else V[1].pb(mp(-a[i], i));
    }
    Rep(i, 2) sort(all(V[i]));

    int res = 0;
    Rep(t, 2){
    	Rep(j, sz(V[t])){
    		int u = V[t][j].se;
    		if(t == 0) u = -u;
//    		cout << u << endl;
    		int before = 0;
    		For(i, 1, n) if(a[u] > a[i] || (a[u] == a[i] && u < i)) before++;
    		a[u] += b[u];
    		int after = 0;
    		For(i, 1, n) if(a[u] > a[i] || (a[u] == a[i] && u < i)) after++;
    		res += abs(before - after);
//    		cout << before << " " << after << endl;
    	}
    }

    cout << res << endl;

    return 0;
}
