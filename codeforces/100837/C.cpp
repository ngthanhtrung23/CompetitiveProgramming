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

ld vw, vc;
int n;
int x[maxn], y[maxn];
ld f[maxn];

ld sqr(ld A){
    return A * A;
}

int main(){
//  freopen("in.txt", "r", stdin);
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> vw >> vc;
    for(int i = 0; i <= n; i++) f[i] = (1ll << 60);
    For(i, 1, n) cin >> x[i] >> y[i];
    f[1] = 0;
    for(int i = 1; i <= n; i++){
        if(i != 1){
            if(y[i] < y[i - 1]){
                for(int j = i - 1; j > 1; j--) if(y[j] > y[i] && y[j - 1] <= y[i]){
                    ld X = (x[j] * (ld)(1.0) * (y[i] - y[j - 1]) + x[j - 1] * (ld)(1.0) * (y[j] - y[i])) / (y[j] - y[j - 1]);
                    ld d = sqrt(sqr(X - x[j - 1]) + sqr(y[i] - y[j - 1]));
                    f[i] = min(f[j - 1] + d / vw + (x[i] - X) / vc, f[i]);
                    break;
                }
            }
        }

        if(i < n){
            ld d = sqrt(sqr(x[i] - x[i + 1]) + sqr(y[i] - y[i + 1]));
            f[i + 1] = min(f[i] + d / vw, f[i + 1]);
            if(y[i] < y[i + 1]){
                for(int j = i + 1; j < n; j++) if(y[j] > y[i] && y[j + 1] <= y[i]){
                    ld X = (x[j] * (ld)(1.0) *(y[i] - y[j + 1]) + x[j + 1] * (ld)(1.0) * (y[j] - y[i])) / (y[j] - y[j + 1]);
                    ld d = sqrt(sqr(X - x[j + 1]) + sqr(y[i] - y[j + 1]));
                    f[j + 1] = min(f[i] + d / vw  + (X - x[i]) / vc, f[j + 1]);
                    break;
                }
            }
        }
    }

    cout << fixed << setprecision(6) << f[n] << endl;

    return 0;
}
