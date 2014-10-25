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

#define maxn 2005

int n, m, d, start[maxn], num[maxn];
vector<int> V[maxn];
II res[maxn];
int main() {
   // freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    d = n / m;
    ms(start, 0);
    ms(num, 0);
    For(i, 1, n){
        int x; cin >> x;
        if(x == -1) x = 0;
        num[x]++;
        V[x].pb(i);
    }

    cout << "Yes" << endl;
    Rep(run, m){
        II P[maxn];
        For(i, 1, m) P[i] = mp(num[i], i);
        sort(P + 1, P + m + 1);
      //  For(i, 0, m) cout << num[i] << " "; cout << endl;
        bool have = false;
        For(i, 1, m) if(P[i].fi > 0){
            //cout << i << " " << P[i].fi << endl;
            have = true;
            if(P[i].fi >= d){
                int t = P[i].se;
                num[t] -= d;
                Rep(id, d) res[V[t][start[t]++]] = mp(t, t);
                break;
            } else if(i != m){
                int t = P[i].se;
                int tt = P[m].se;
                Rep(id, num[t]) {
                    res[V[t][start[t]++]] = mp(t, tt);
                }
                Rep(id, min(d - num[t], num[tt])) {
                    res[V[tt][start[tt]++]] = mp(tt, t);
                }
                for(int id = num[tt]; id < d - num[t]; id++){
                    res[V[0][start[0]++]] = mp(tt, t);
                }

                num[tt] = max(0, num[tt] - (d - num[t]));
                num[t] = 0;
            } else{

                int t = P[m].se;
                Rep(id, min(d, num[t])) {
                    res[V[t][start[t]++]] = mp(t, t);
                }
                for(int id = min(d, num[t]); id < d; id++){
                    res[V[0][start[0]++]] = mp(t, t);
                }
                num[t] = 0;
            }
            break;
        }
        if(!have){
           // cout << "dm" << endl;
            Rep(id, d) res[V[0][start[0]++]] = mp(1, 1);
        }

    }
    for(int i = 1; i <= n; i++) cout << res[i].fi << " " << res[i].se << "\n";

    return 0;
}
