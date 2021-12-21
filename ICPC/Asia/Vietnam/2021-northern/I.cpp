#include <bits/stdc++.h>
//#include "RNG.h"
using namespace std;
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define inf 1000000005
#define linf (1ll << 60)
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
#define eps 1e-6
typedef pair<int, int> II;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI 2 * acos(0)

const int maxn = 1000005;
const int MAX = 4000005;

int n;
ld a[maxn], sum[maxn], mul[maxn], fact[maxn], f[maxn];
int cnt[maxn];

void solution(){
//    freopen("in.txt", "r", stdin);

    cin >> n;
    Rep(i, n) cin >> a[i];
    sum[0] = 0;
    For(mask, 1, (1 << n) - 1){
        Rep(i, n) if(getbit(mask, i)){
            sum[mask] = sum[offbit(mask, i)] + a[i];
            break;
        }
    }

    fact[0] = 1;
    For(i, 1, n) fact[i] = fact[i - 1] * i;

    ld l = 0, r = (1 << 20);

    Rep(run, 70){
        ld mid = (l + r) / 2;
        ld ret = 0;
        for (int mask = (1 << n) - 1; mask >= 0; mask--) if (getbit(mask, 0)) {
            f[mask] = sum[mask] - __builtin_popcount(mask) * mid;
            if (mask != (1<<n) - 1){
                ld TT = 0, prob = (ld)(1.0) / (n - __builtin_popcount(mask));
                Rep(i, n) if(!getbit(mask, i)){
                    TT += f[onbit(mask, i)];
                }
                TT *= prob;
                f[mask] = max(f[mask], TT);
            }
            ret += f[mask]
                * fact[n - __builtin_popcount(mask)]
                * fact[__builtin_popcount(mask) - 1];
        }
        if (ret > 0) l = mid;
        else r = mid;

    }
    cout << fixed << setprecision(10) << l << endl;
}

int main(){
    solution();
    return 0;
}
