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

int n;
ll m;
vector<pair<ll, int> > V1, V2;

int main() {
   // freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    ll gt, id;
    For(i, 1, n){
        cin >> gt >> id;
        if(id) V1.pb(mp(gt, i));
        else V2.pb(mp(gt, i));
    }

    sort(all(V1)); sort(all(V2));
    ll run = (int)sz(V2) - 1, T = 0;
    while(T < m && run >= 0){
        T += V2[run].fi;
        run--;
    }
    II res = mp(inf, inf);

    for(int i = sz(V1); i >= 0; i--){
        if(T >= m){
            while(run + 1 < sz(V2) && T - V2[run + 1].fi >= m){
                T -= V2[run + 1].fi;
                run++;
            }
            int A = sz(V1) - i;
            int B = sz(V2) - run - 1;
            res = min(res, mp(A + B, B));
        }

        if(i) T += V1[i - 1].fi;
    }

    int C = res.fi, B = res.se;
    int A = C - B;
    cout << C << " " << A << endl;
    For(i, 1, A) cout << V1[sz(V1) - i].se << " ";
    For(i, 1, B) cout << V2[sz(V2) - i].se << " ";

    return 0;
}
