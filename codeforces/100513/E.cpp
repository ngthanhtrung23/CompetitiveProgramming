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

int n, a[maxn], b[maxn];
int f[maxn];

int main() {
    //freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int number = 0;
    For(i, 1, n) {
        cin >> a[i] >> b[i];
        if(a[i] > b[i]) number++;
    }

    if(number == 0){
        cout << -1 << endl;
        return 0;
    }

    int RR = n - (number + number - 1);
    if(RR <= 0){
        cout << 0 << endl;
        return 0;
    }

    f[0] = 0;
    f[1] = 0;
    for(int i = 2; i <= n; i++){
        f[i] = f[i - 1];
        int d = 0;
        int t1 = (a[i] > b[i]) ? 1 : 0;
        int t2 = (a[i - 1] > b[i - 1]) ? 1 : 0;
        int t3 = (a[i] + a[i - 1] > b[i] + b[i - 1]) ? 1 : 0;
        if(!t1 && !t2) d = 1;
        if((t1 ^ t2) && t3) d = 1;
        f[i] = max(f[i], f[i - 2] + d);
        if(f[i] >= RR){
            int vt = i;
            vector<II> res;
            cout << RR << endl;
            while(vt > 0 && RR > 0){
                if(f[vt] == f[vt - 1]) vt--;
                else {
                    res.pb(mp(vt - 1, vt));
                    RR--;
                    vt -= 2;
                }
            }
            for(int j = sz(res) - 1; j >= 0; j--) cout << res[j].fi << " " << res[j].se << "\n";
            return 0;
        }
    }

    cout << -1 << endl;

    return 0;
}