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

vector<string> res;

int n, a[maxn];
II P[maxn];

int main()
{
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    For(i, 1, n) cin >> a[i];

    while(true){
    	string temp;
    	temp.resize(n);
    	Rep(i, n) temp[i] = '0';
    	For(i, 1, n) P[i] = mp(a[i], i);
    	sort(P + 1, P + n + 1);
    	int first = 1;
    	while(P[first].fi < P[n].fi){
    		first++;
    	}
    	if(first == 1) break;
    	int d = (n - first + 1);
    	if(first == n) first = n - 1;
    	else if(d & 1){
    		first = n - 2;
    	} else first = n - 1;
    	For(i, first, n){
    		a[P[i].se] = max(0, a[P[i].se] - 1);
    		temp[P[i].se - 1] = '1';
    	}
    	res.pb(temp);
    }

    cout << a[1] << "\n" << sz(res) << "\n";
    Rep(i, sz(res)) cout << res[i] << "\n";

    return 0;
}
