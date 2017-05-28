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

#define maxn 500005

string s, temp;

int main()
{
//	freopen("in.txt", "r", stdin);

	ios::sync_with_stdio(0);
	cin.tie(0);

	s = "abbabbb";
	char cur = 'b';
	for(int i = 5; i <= 19; i += 2){
		temp = s;
		s = "";
		int n = sz(temp);
		bool first = true;
		Rep(j, n){
			s.push_back(temp[j]);
			if(j != n - 2 && temp[j] == cur) {
				s.push_back(cur + 1);
				if(first) {
					s.push_back(cur + 1);
					first = false;
				}
			}
		}
		s.push_back(cur + 1);
		s.push_back(cur + 1);
		cur++;
	}
//	cout << s  << endl;
	int N;
	cin >> N;
	int n = sz(s);
	int run = 0;
	string res = "";
	Rep(i, n){
		res.push_back(s[i]);
		if(i != n - 2 && s[i] == cur){
			if(getbit(N, run)){
				res.push_back(cur + 1);
			}
			run++;
		}
	}
	cout << res << " abcdefghijk" << endl;

	return 0;
}
