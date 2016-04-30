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
#define y1 y32432
#define y2 y435346

#define maxn 2000005

string s, t, ss;
int l[maxn][3], r[maxn][3], f[maxn];
int vt[3];
pair<int, int> VV[4];

int cal(){

	int n = s.length();
	ss = s + s;
//	cout << s << " " << ss << endl;
	ms(f, -1);
	for(int i = 0; i < n + n; i++){
		vt[ss[i] - 'a'] = i;
		if(i >= n){
			for(int j = 0; j < 3; j++) {
	//    			cout << i << " " << j << " " << vt[j] << endl;
				l[i - n][j] = i - vt[j];
			}
		}
	}

	for(int i = n + n - 1; i >= 0; i--){
		vt[ss[i] - 'a'] = i;
		if(i < n){
			for(int j = 0; j < 3; j++) {
				r[i][j] = vt[j] - i;
	//    			cout << i << " " << j << " " << vt[j] << endl;
			}
		}
	}

	for(int i = 0; i < n; i++) if(t[i] == '*'){
		int c = s[i] - 'a';
		int u = (c + 1) % 3, v = (c + 2) % 3;
		int A = max(r[i][0], max(r[i][1], r[i][2]));
		int B = max(l[i][0], max(l[i][1], l[i][2]));
//		cout << A << " " << B << endl;
		VV[0] = (mp(A, -1));
		VV[1] = (mp(0, B));
		VV[2] = (mp(r[i][u], l[i][v]));
		VV[3] = (mp(r[i][v], l[i][u]));
		sort(VV, VV + 4);
//		cout << i << endl;
//		Rep(j, 4) cout << VV[j].fi << " " << VV[j].se << endl;
		for(int j = 1; j < 4; j++){
			VV[j].se = min(VV[j].se, VV[j - 1].se);
		}
		for(int j = 1; j < 4; j++){
			f[VV[j].fi - 1] = max(f[VV[j].fi - 1], VV[j - 1].se);
		}
	}

	int res = inf;
	int run = -1;
	for(int i = maxn - 1; i >= 0; i--){
		run = max(run, f[i]);
		if(run < 0) res = min(res, i);
		else res = min(res, run + i * 2);
	}
	return res;

}

string reverse(string x){
	string res = "";
	for(int i = x.length() - 1; i >= 0; i--){
		res.pb(x[i]);
	}
	return res;
}
int main(){
//	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> t;
    int res = cal();
    reverse(all(s));
    reverse(all(t));
    res = min(res, cal());
    cout << res << endl;

    return 0;
}
