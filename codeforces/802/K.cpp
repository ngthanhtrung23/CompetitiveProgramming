#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;
const ld PI = acos((ld) -1);
const ld EPS = 1e-9;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
inline int sign(ld x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(ld x, ld y) {return sign(x - y);}
#define db(x) cerr << #x << " = " << (x) << ", ";
#define endln cerr << "\n";
#define chkpt cerr << "-----\n";

const int maxn = 1e5 + 5;
int n, k;
vii adj[maxn];
long long f[maxn];
long long g[maxn];

void dfs(int u, int p) {
    vector<long long> vf, vg;
    FOR(i, 0, sz(adj[u])) {
        int v = adj[u][i].fi;
        int w = adj[u][i].se;
        if (v != p) {
            dfs(v, u);
            vf.pb(f[v] + w);
            vg.pb(g[v] + w);
        }
    }
    set<pair<long long, int> > heap, rem;
    long long tot = 0;
    FOR(i, 0, sz(vf)) {
        long long x = vf[i];
        heap.insert(mp(x, i));
        tot += x;
    }
    while (sz(heap) > k - 1) {
        tot -= heap.begin()->fi;
        rem.insert(*heap.begin());
        heap.erase(heap.begin());
    }
    FOR(i, 0, sz(vf)) {
        long long x = vf[i];
        long long y = vg[i];
        if (present(heap, mp(x, i))) {
            if (sz(rem)) {
                chkmax(g[u], y + tot - x + rem.rbegin()->fi);
            }
            else {
                chkmax(g[u], y + tot - x);
            }
        }
        else {
            chkmax(g[u], y + tot);
        }
    }
    sort(all(vf), greater<long long>());
    while (sz(vf) > k - 1) vf.pop_back();
    FOR(i, 0, sz(vf)) f[u] += vf[i];
}

void solve() {
    cin >> n >> k;
    FOR(i, 0, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb(mp(v, w));
        adj[v].pb(mp(u, w));
    }
    dfs(0, -1);
    cout << max(f[0], g[0]) << "\n";
}

int main() {
    int JUDGE_ONLINE = 1;
    if (fopen("in.txt", "r")) {
        JUDGE_ONLINE = 0;
        assert(freopen("in.txt", "r", stdin));
        //assert(freopen("out.txt", "w", stdout));
    }
    else {
        ios_base::sync_with_stdio(0), cin.tie(0);
    }
    solve();
    if (!JUDGE_ONLINE) {
        //cout << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    }
    return 0;
}
