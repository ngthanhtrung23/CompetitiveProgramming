#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

using namespace std;

typedef long long ll;
typedef double ld;
typedef unsigned int ui;
typedef unsigned long long ull;

#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)
#define Fit(i,v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
#define Fitd(i,v) for(__typeof((v).rbegin()) i = (v).rbegin(); i != (v).rend(); ++i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))

template<class F, class T> T convert(F a, int p = -1) { stringstream ss; if (p >= 0) ss << fixed << setprecision(p); ss << a; T r; ss >> r; return r; }
template<class T> T gcd(T a, T b) { T r; while (b != 0) { r = a % b; a = b; b = r; } return a; }
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
template<class T> T sqr(T x) { return x * x; }
template<class T> T cube(T x) { return x * x * x; }
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return s == 0 ? 0 : cntbit(s >> 1) + (s & 1); }
const int bfsz = 1 << 16; char bf[bfsz + 5]; int rsz = 0;int ptr = 0;
char gc() { if (rsz <= 0) { ptr = 0; rsz = (int) fread(bf, 1, bfsz, stdin); if (rsz <= 0) return EOF; } --rsz; return bf[ptr++]; }
void ga(char &c) { c = EOF; while (!isalpha(c)) c = gc(); }
int gs(char s[]) { int l = 0; char c = gc(); while (isspace(c)) c = gc(); while (c != EOF && !isspace(c)) { s[l++] = c; c = gc(); } s[l] = '\0'; return l; }
template<class T> bool gi(T &v) {
    v = 0; char c = gc(); while (c != EOF && c != '-' && !isdigit(c)) c = gc(); if (c == EOF) return false; bool neg = c == '-'; if (neg) c = gc();
    while (isdigit(c)) { v = v * 10 + c - '0'; c = gc(); } if (neg) v = -v; return true;
}

typedef pair<int, int> II;

const double PI = acos(-1.0);
const double eps = 1e-9;

const int dr[] = {-1, 0, +1, 0};
const int dc[] = {0, +1, 0, -1};

const int inf = (int)1e9 + 5;
const ll linf = (ll)1e17 + 5;
const ll mod = (ll)1e9 + 7;

#define maxn 20

int dau[1 << maxn], cuoi[1 << maxn], sum[1 << maxn];
bool can[1 << maxn][maxn];
II P[maxn];
int test = 0;
int n;

void init(){
	ms(dau, -1);
	For(mask, 1, (1 << 20) - 1){
		Rep(i, 20) if(getbit(mask, i)){
			if(dau[mask] == -1) {
				dau[mask] = i;
			}
			cuoi[mask] = i;
		}
	}
}

void solve(){
	Rep(i, n){
		cin >> P[i].fi >> P[i].se;
	}
	sort(P, P + n);
	sum[0] = 0;
	For(mask, 1, (1 << n) - 1) {
		sum[mask] = sum[offbit(mask, dau[mask])] + P[dau[mask]].fi;
	}
	For(mask, 1, (1 << n) - 1){
		Rep(i, n){
			if(!getbit(mask, i)){
				can[mask][i] = 0;
				if(i < dau[mask]){
					can[mask][i] = (P[i].fi + P[i].se >= P[dau[mask]].fi ? 1 : 0);
				}
				else if(i > cuoi[mask]){
					can[mask][i] = (P[i].fi - P[i].se <= P[cuoi[mask]].fi ? 1 : 0);
				}
				else{
					if(abs(sum[mask] / __builtin_popcount(mask) - P[i].fi) <= P[i].se) can[mask][i] = 1;
					if(!can[mask][i]){
						for(int j = dau[mask]; j <= cuoi[mask]; j++) if(getbit(mask, j)){
							if(can[offbit(mask, j)][i]){
								can[mask][i] = 1;
								break;
							}
						}
					}
				}
			}
			else can[mask][i] = 1;
		}
	}
	int res = inf;
	bool check;
	For(mask, 1, (1 << n) - 1){
		check = true;
		Rep(i, n) if(!can[mask][i]){
			check = false;
			break;
		}
		if(check){
			res = min(res, __builtin_popcount(mask));
		}
	}
	cout << "Case " << ++test << ": " << res << endl;
}

void gen(){
	freopen("in.txt", "w", stdout);
	Rep(run, 10){
		cout << 20 << endl;
		Rep(i, 20){
			cout << rand() + 1<< " " << rand() % 20 << endl;
		}
	}
}

int main(){
//	gen();

//	freopen("in.txt", "r", stdin);
	init();
	while(cin >> n){
		solve();
	}
//	cout << clock() << endl;
	return 0;
}


