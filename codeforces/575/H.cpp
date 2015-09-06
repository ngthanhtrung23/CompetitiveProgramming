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
typedef long double ld;
#define eps 1e-9
typedef pair<int, int> II;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI 2 * acos(0)

#define maxn 2000005

ll fact[maxn], inv[maxn];

ll mu(ll x, ll k){
    if(k == 0) return 1;
    if(k & 1) return mu(x, k - 1) * x % mod;
    ll t = mu(x, k >> 1);
    return t * t % mod;
}

int main() {
//  freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    fact[0] = 1;
    For(i, 1, maxn - 1) fact[i] = fact[i - 1] * i % mod;
    Rep(i, maxn / 2) inv[i] = mu(fact[i], mod - 2);

    ll RR = 1, res = 0;
    int n;
    cin >> n;
    For(i, 0, n + n){
        res = (res + RR) % mod;
//      cout << RR << endl;
        ll T = 0;
        if(i >= n){
            T = (fact[i] * inv[n]) % mod * inv[i - n] % mod * 2 % mod;
        }
        RR = (RR * 2 - T + mod) % mod;
    }
    cout << res << endl;

//  cout << clock() << endl;

    return 0;
}
