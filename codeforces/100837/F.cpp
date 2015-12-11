#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define Fit(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
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

#define maxn 100005

ll f[1 << 16][16][6];

int n, m, c[16][16], h[1 << 17];

ll cal(int mask, int id, int height){
    if(f[mask][id][height] != -1) return f[mask][id][height];
//  cout << mask << " " << id << endl;
    ll &res = f[mask][id][height];
    if(cntbit(mask) == 1) return res = 1;
    res = 0;
    for(int mask1 = mask; mask1 > 0; mask1 = (mask1 - 1) & mask) if(getbit(mask1, id) && mask1 != mask){
        int mask2 = mask ^ mask1;
        if(height > h[mask1] && height > h[mask2]){
            for(int j = 0; j < n; j++) if(c[id][j] && getbit(mask2, j)){
                res += cal(mask1, id, height - 1) * cal(mask2, j, height - 1);
            }
        }
    }
    return res;

}

int main(){
//  freopen("in.txt", "r", stdin);
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ms(f, -1);
    cin >> n >> m; m--;
    Rep(i, n) Rep(j, n) cin >> c[i][j];

//    cout << cntbit(511) << endl;

    For(i, 1, (1 << 16) - 1){
        int A = int(log(cntbit(i) - 0.5) / log(2)) + 1;
//      if(i == (1 << 16) - 1) cout << A << endl;
//      if(i == 1) cout << A << endl;
        h[i] = A;
    }

    cout << cal((1 << n) - 1, m, h[(1 << n) - 1]) << endl;

    return 0;
}
