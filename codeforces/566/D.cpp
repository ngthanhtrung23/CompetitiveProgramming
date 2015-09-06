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
typedef long double ld;
#define eps 1e-9
typedef pair<int, int> II;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI 2 * acos(0)

#define maxn 500005

int nex[maxn], dad[maxn];
int n, q;

int getdad(int x){
	if(dad[x] == x) return x;
	return dad[x] = getdad(dad[x]);
}

void go(int x, int y){
	int dx = getdad(x);
	int dy = getdad(y);
	if(dx != dy){
		if(dx > dy) swap(dx, dy);
		dad[dy] = dx;
	}
}

int go1(int id, int y){
	int u = nex[id];
	if(u >= y) return u;
	else{
		int v = u + 1;
		go(u, v);
		return nex[id] = nex[u] = nex[v] = go1(v, y);
	}
}

int main(){
//  freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    int id, x, y;
    For(i, 1, n) {
    	nex[i] = i;
    	dad[i] = i;
    }

    Rep(run, q){
    	cin >> id >> x >> y;
    	if(id == 1) {
    		go(x, y);
    	} else if(id == 3){
    		int dx = getdad(x);
    		int dy = getdad(y);
    		if(dx == dy){
    			cout << "YES\n";
    		} else cout << "NO\n";
    	} else{
    		nex[x] = go1(x, y);
    	}
    }

    return 0;
}