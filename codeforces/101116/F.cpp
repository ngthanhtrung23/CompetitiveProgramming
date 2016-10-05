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
typedef long double ld;
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxn 1005

ll n;
II P[maxn];
vector<int> V;
int test;

ld R = 6371;

ld deg2rad(ld x){
	return x / 180 * PI;
}

ld distanceEarth(ld lat1d, ld lon1d, ld lat2d, ld lon2d) {
  ld lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * R * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void solve(){
	cout << fixed << setprecision(8);
	ld a1, b1, a2, b2;
	cin >> a1 >> b1 >> a2 >> b2;
	ld x = abs(a1);
	ld g = cos(x / 90 * PI / 2);
	ld y = min(abs(b1 - b2), 360 - abs(b1 - b2));
	ld A = y / 360 * 2 * PI * g;

	ld B = abs(a1 - a2) / 180 * PI;
	ld res2 = (A + B) * R;

	ld res1 = distanceEarth(a1, b1, a2, b2);
	cout << res1 << " " << res2 << "\n";


//	cout << PI << endl;
}

int main(){
//	freopen("in.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> test;
	Rep(itest, test) solve();
    return 0;
}
