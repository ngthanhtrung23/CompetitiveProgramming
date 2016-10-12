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

#define maxn 100005

int n, sum;
int f[maxn], kq;
vector<II> res;
bool check = false;

void danh(int a, int b){
	if(f[a] > f[b]) swap(a, b);
	f[b] -= f[a];
	f[a] += f[a];
	res.pb(mp(a, b));
	if(f[a] == kq || f[b] == kq) check = true;
}

void dap(int u){
//	cout << u << " " << f[u] << " " << f[1] << " " << f[2] << endl;
	if(check) return;
	danh(1, 2);
	if(check) return;
	while(f[u] >= f[1]) {
//		cout << u << " " << f[u] << endl;
		if(check) break;
		danh(1, u);
	}
//	cout << f[1] << " " << f[2] << endl;
	if(check) return;
	while(f[1] != 1) {
		if(check) break;
		danh(1, 2);
	}
//	cout << "zzz" << endl;
	if(f[u] > 1) dap(u);
}

int main()
{
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    sum = 0;
    For(i, 1, n) {
    	sum += i;
    	f[i] = i;
    }

    kq = sum - 1;
    if(sum % 2 == 0) kq--;

    int last = -1;
    for(int i = 3; i <= n; i++){
    	while(f[i] > 1) dap(i);
    	if(f[i] > 0 && !check){
    		if(last == -1) last = i;
    		else{
    			danh(i, last);
    			dap(i);
    		}
    		if(f[i] > 0) last = i;
    	}
    }

    cout << sz(res) << endl;
    Rep(i, sz(res)) cout << res[i].fi << " " << res[i].se << endl;

    return 0;
}
