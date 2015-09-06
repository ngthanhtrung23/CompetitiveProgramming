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

#define maxn 800005

struct node{
	int next[26];
	int back;
	set<int> S[2];
};

node T[maxn];
int run = 0, n;
bool flag[maxn][2];

void add(int id, int vt, string s){
	int root = 0;
	Rep(i, sz(s)){
		int c = s[i] - 'a';
		if(T[root].next[c]){
			int u = T[root].next[c];
			T[u].S[id].insert(vt);
			root = u;
		} else{
			T[root].next[c] = ++ run;
			int u = run;
			T[u].back = root;
			T[u].S[id].insert(vt);
			root = u;
		}
	}
}

int main(){
//  freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    string s;

    ms(T[0].next, 0);

    Rep(rrrrr, n){
    	cin >> s;
    	add(0, rrrrr + 1, s);
    }

    Rep(rrrr, n) {
    	cin >> s;
    	add(1, rrrr + 1, s);
    }

    ll res = 0;
    vector<II> V;
    ms(flag, 0);

    for(int i = run; i >= 1; i--){
    	while(sz(T[i].S[0]) && sz(T[i].S[1])){
    		int u = *T[i].S[0].begin();
    		int v = *T[i].S[1].begin();
    		flag[u][0] = 1;
    		flag[v][1] = 1;
    		int RR = i;
    		V.push_back(mp(u, v));
    		while(RR){
    			res++;
    			T[RR].S[0].erase(u);
    			T[RR].S[1].erase(v);
    			RR = T[RR].back;
    		}
    	}
    }

    cout << res << endl;

    int uu = 1, vv = 1;
    while(sz(V) < n){
    	while(flag[uu][0]) uu++;
    	while(flag[vv][1]) vv++;
    	V.pb(mp(uu, vv));
    	uu++; vv++;
    }

    Rep(i, sz(V)) cout << V[i].fi << " " << V[i].se << "\n";

    return 0;
}