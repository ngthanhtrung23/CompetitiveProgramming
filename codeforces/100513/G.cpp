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
template<class T> int cntbit(T s) { return __builtin_popcountll(s);}
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef double ld;
#define eps 1e-9
typedef pair<int, int> II;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI 2 * acos(0)

#define maxn 300005

int n, m;
ll a[maxn], MIN;

int main() {
  //  freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    MIN = inf;
    For(i, 1, n){
        cin >> a[i];
        MIN = min(MIN, a[i]);
    }

    ll sum = 0; For(i, 1, m) sum += a[i];
    ll res = 0;
    Ford(i, m, 1){
        if(sum < 0) break;
        else {
            ll d = sum + 1;
            ll t = a[i] - MIN;
            ll sub = min(t, d);

            a[i] -= sub;
            res += sub;
            sum -= sub;
        }
    }

    For(i, m + 1, n){
        sum += a[i] - a[i - m];
        if(sum >= 0){
            ll d = sum + 1;
            ll t = a[i] - MIN;
            ll sub = min(t, d);
            a[i] -= sub;
            res += sub;
            sum -= sub;
        }
    }

    cout << res << endl;
    For(i, 1, n) cout << a[i] << " ";

    return 0;
}