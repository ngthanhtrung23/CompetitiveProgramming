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

int n, m;
vector<int> V[maxn];
int deg[maxn];
vector<II> res;
bool flag[maxn];

void go(int par, int u){
	flag[u] = 1;
	Rep(i, sz(V[u])){
		int v = V[u][i];
		if(v == par) continue;
		if(!flag[v]){
			go(u, v);
			if(deg[v] % 2 == 0){
				deg[u]++;
				deg[v]++;
				res.pb(mp(u, v));
			}
		}
	}
}

int main()
{
//	freopen("in.txt", "r", stdin);
//    ios::sync_with_stdio(0);
//    cin.tie(0);

    scanf("%d %d", &n, &m);
    Rep(run, m){
    	int u, v;
    	scanf("%d %d", &u, &v);
    	V[u].pb(v);
    	V[v].pb(u);
    }
    ms(deg, 0); ms(flag, 0);
    bool ok = true;
    For(i, 1, n) if(!flag[i]){
    	go(0, i);
    	if(deg[i] % 2 == 0){
    		ok = false;
    	}
    }

    if(ok){
    	printf("%d\n", (int)sz(res));
    	Rep(i, sz(res))
    		printf("%d %d\n", res[i].fi, res[i].se);
    } else cout << -1 << endl;

    return 0;
}
