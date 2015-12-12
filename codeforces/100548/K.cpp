
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

ll f(ll a, ll b) {
	if (a == 0 && b == 0) return 1;
	if (a == b) return 2;
	if (a == 0) return 2;
	if (b == 0) return 2;
	
	if (a < b) swap(a, b);

	ll aa = a % b;
	if (aa == 0) aa = b;
	
	return f(b, aa) + (a - aa) / b;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	ll a, b;
	int ntest; cin >> ntest;
	FOR(test,1,ntest) {
		cin >> a >> b;
		cout << "Case #" << test << ": " << f(a, b) << endl;
	}
}
