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
template<class T> int cntbit(T s) { return __builtin_popcountll(s);}
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define eps 1e-6
typedef pair<int, int> II;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI 2 * acos(0)
#define maxn 10005
#define y1 y32434534

ll n;

void sol(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//    freopen("in.txt", "r", stdin);

    cin >> n;
    ll resw = 0, resl = 0, rest = n * n;

    ll run = 1, type = 1;

    while(run <= n){

    	ll x = n / run;
    	ll y = (x + 1) / 2;
    	ll ret = y * y;

    	if(!type){
    		ret = (n / run) * (n / run) - (n  / (run + run)) * (n / (run + run));
    	}

    	if(type) resl += ret;
    	else resw += ret;
    	rest -= ret;

    	run += run;
    	type = 1 - type;
    }

    cout << resw << endl << rest << endl << resl << endl;

}

int main(){
	sol();

	return 0;
}
