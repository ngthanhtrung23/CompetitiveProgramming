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

const int MAXN = 1e5 + 5;
const int MAXC = 26;
struct state {
    int len, link, fpos;
    int nxt[MAXC];
};
struct SuffixAutomaton {
    state st[MAXN << 1];
    int nsz, last;
    int cnt[MAXN << 1];
    long long nchild[MAXN << 1];
    void init() {
        st[0].len = 0;
        st[0].link = -1;
        st[0].fpos = 0;
        memset(st[0].nxt, -1, sizeof(st[0].nxt));
        nsz = 1; last = 0;
        cnt[0] = nchild[0] = 0;
    }
    void extend(char c) {
        int cur = nsz++;
        st[cur].len = st[last].len + 1;
        st[cur].fpos = st[cur].len - 1;
        memset(st[cur].nxt, -1, sizeof(st[cur].nxt));
        cnt[cur] = 1; nchild[cur] = 0;
        int p;
        for (p = last; ~p && !~st[p].nxt[c]; p = st[p].link) st[p].nxt[c] = cur;
        if (!~p) st[cur].link = 0;
        else {
            int q = st[p].nxt[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = nsz++;
                st[clone].len = st[p].len + 1;
                memcpy(st[clone].nxt, st[q].nxt, sizeof(st[q].nxt));
                st[clone].link = st[q].link;
                st[clone].fpos = st[q].fpos;
                cnt[clone] = 0; nchild[clone] = 0;
                for (; ~p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    long long updatesize() {
        vector<int> v, vis(nsz, 0);
        queue<int> q;
        q.push(0); vis[0] = 1;
        while (q.size()) {
            int u = q.front(); q.pop();
            v.push_back(u);
            for (int i = 0; i < MAXC; i++) {
                if (~st[u].nxt[i] && !vis[st[u].nxt[i]]) {
                    q.push(st[u].nxt[i]);
                    vis[st[u].nxt[i]] = 1;
                }
            }
        }
        long long res = 0;
        for (int i = v.size() - 1; i > 0; i--) {
            int u = v[i];
            cnt[st[u].link] += cnt[u];
            res += (long long) cnt[u] * cnt[u] * (st[u].len - st[st[u].link].len);
        }
        return res;
    }
} sa;

void solve() {
    int test; cin >> test;
    while (test--) {
        string s; cin >> s;
        sa.init();
        for (int i = 0; i < s.size(); i++) {
            sa.extend(s[i] - 'a');
        }
        cout <<  sa.updatesize() << "\n";
    }
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
