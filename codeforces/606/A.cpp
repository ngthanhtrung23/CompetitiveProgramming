
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

void update(int a, int x, int& has, int& need) {
	if (a > x) has += (a - x) / 2;
	else need += x - a;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	int a, b, c, x, y, z;
	while (cin >> a >> b >> c >> x >> y >> z) {
		int has = 0, need = 0;
		update(a, x, has, need);
		update(b, y, has, need);
		update(c, z, has, need);

		if (has >= need) cout << "Yes"; else cout << "No";
		cout << endl;
	}
}
