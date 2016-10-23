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

#define maxn 21005

II f[maxn], g[maxn];
II P[maxn];
int add = 10005;
int n;

II adds(II P1, II P2){
	return mp(P1.fi + P2.fi, P1.se + P2.se);
}

int main()
{
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    For(i, 1, n) cin >> P[i].fi;
    For(i, 1, n) cin >> P[i].se;

    Rep(i, maxn) f[i] = mp(inf, inf);
    f[add] = mp(0, 0);
    For(t, 1, n){
    	Rep(i, maxn){
    		g[i] = f[i];
    		f[i] = mp(inf, inf);
    	}
    	Rep(i, maxn) if(g[i].fi < inf){
    		f[i + P[t].se - P[t].fi] = min(f[i + P[t].se - P[t].fi], adds(g[i], mp(1, 0)));
    		f[i - P[t].fi] = min(f[i - P[t].fi], adds(g[i], mp(0, P[t].fi)));
    	}
    }

    II res = mp(inf, inf);
    for(int i = add; i < maxn; i++) res = min(res, f[i]);
    cout << res.fi << " " << res.se << endl;

    return 0;
}
