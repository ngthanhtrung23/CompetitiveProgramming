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

#define maxn 1000005

int n;
vector<int> V[maxn];
int deg[maxn];
ll h[maxn];
vector<int> VV;
bool flag[maxn];
ll res = 1;
ll fact[maxn];

ll hash(ll x){
	return x * x * x * x + 37 * x * x + 119 * x + 335681;
}

void go(int par, int u){
	map<ll, ll> M;
	map<ll, ll>::iterator it;
	ll RR = 0;
	Rep(i, sz(V[u])){
		int v = V[u][i];
		if(v == par) continue;
		go(u, v);
		RR += h[v];
		M[h[v]]++;
	}

	for(it = M.begin(); it != M.end(); it++){
		res = res * fact[(*it).se] % mod;
	}

	h[u] = hash(RR);
}

int main(){
//	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    ms(deg, 0);

    Rep(run, n - 1){
    	int u, v;
    	cin >> u >> v;
    	V[u].pb(v);
    	V[v].pb(u);
    	deg[u]++;
    	deg[v]++;
    }

    for(int i = 1; i <= n; i++) if(deg[i] == 1){
    	VV.pb(i);
    }

    int run = n; ms(flag, 0);
    while(run > 2){
    	vector<int> temp;
    	Rep(i, sz(VV)){
    		int u = VV[i];
    		flag[u] = 1;
    		Rep(j, sz(V[u])){
    			int v = V[u][j];
    			deg[v]--;
    			if(!flag[v] && deg[v] == 1){
    				temp.pb(v);
    			}
    		}
    	}
    	run -= sz(VV);
    	VV = temp;
    }

    int root = n + 1;

    if(run == 1){
    	For(i, 1, n) if(!flag[i]){
    		root = i;
    	}
    } else{
    	int u = -1, v = -1;
    	For(i, 1, n) if(!flag[i]){
    		if(u == -1) u = i;
    		else v = i;
    	}
    	Rep(i, sz(V[u])){
    		int x = V[u][i];
    		if(x == v) V[u].erase(V[u].begin() + i);
    	}
    	Rep(i, sz(V[v])){
    		int x = V[v][i];
    		if(x == u) V[v].erase(V[v].begin() + i);
    	}
    	V[u].pb(root); V[v].pb(root);
    	V[root].pb(u); V[root].pb(v);
    }

    fact[0] = 1;
    For(i, 1, maxn - 1) fact[i] = fact[i - 1] * i % mod;
//    cout << root << endl;
    go(0, root);

    cout << res << endl;

    return 0;
}
