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
#define sz(a) ((ll)(a).size())

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcnt(s);}
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
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxn 5005

string s, temp;

int test;
ld a[maxn];

ld sqr(ld x){
	return x * x;
}

int cal(ld ave){
	int res = (int)(ave);
	if(ave - res > 0.5) res++;
	return res;
}

void solve(){
//	ld sum = 0;
	int n = 250;
	For(i, 1, n) {
		cin >> a[i];
	}

	sort(a + 1, a + n + 1);
	int number = 0;
	For(i, 1, n){
		if(a[i] >= a[n] * 0.8 - eps){
			number++;
		}
	}

//	cout << a[250] << endl;
	if(number >= 10){
		if(a[n] >= 0){
			int dem = 0;
			For(i, 1, n){
				if(a[i] <= a[n] * 0.2 + eps && a[i] >= 0){
					dem++;
				}
			}
			if(dem > number + number + number){
				cout << "poisson" << endl;
				return;
			}
//			cout << dem << " " << number << endl;
		}
		cout << "uniform" << endl;
//		cout << RRR << endl;
	} else{
		cout << "poisson" << endl;
//		cout << cal(ave) << endl;
	}
}

int main()
{
//	freopen("in.txt", "r", stdin);

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> test;
	Rep(itest, test){
		solve();
	}

	return 0;
}
