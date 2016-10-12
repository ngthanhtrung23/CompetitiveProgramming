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
template<class T> int cntbit(T s) { return __builtin_popcount(s);}
#define Rep(i,n) for(ll i = 0; i < (n); ++i)
#define Repd(i,n) for(ll i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(ll i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(ll i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define eps 1e-12
typedef pair<ll, ll> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos((ld)0))
#define linf (1ll << 60)
#define y1 y32432
#define y0 y435346

#define maxn 205

ll n;

struct Point{
	ld x, y;
	Point(){};
	Point(ld _x, ld _y){
		x = _x;
		y = _y;
	}
};

ld sqr(ld x){
	return x * x;
}

ld dist(Point p0, Point p1){
	return sqrt(sqr(p0.x - p1.x) + sqr(p0.y - p1.y));
}

ld d[205][205];
Point P[205];

int main()
{
//	freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> P[0].x >> P[0].y >> P[1].x >> P[1].y;
    n = 2;
    ld x, y;
    bool have = 0;

    for(int i = 0; i < maxn; i++) for(int j = 0; j < maxn; j++) d[i][j] = 1e15;

    while(cin >> x >> y){
    	if(x < -0.5){
    		have = 0;
    	} else{
    		P[n].x = x; P[n].y = y;
    		if(have) d[n - 1][n] = d[n][n - 1] = dist(P[n - 1], P[n]) / 40;
    		have = 1;
    		n++;
    	}
    }

    Rep(i, n) Rep(j, n) d[i][j] = min(d[i][j], dist(P[i], P[j]) / 10);

    Rep(k, n) Rep(i, n) Rep(j, n) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    ld res = d[0][1] * 60 / 1000;
    cout << fixed << setprecision(0) << res << "\n";

    return 0;
}
