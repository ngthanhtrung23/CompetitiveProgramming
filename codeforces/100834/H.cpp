
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

const int MN = 111;

int n;
struct Perm {
	int x[MN];

	friend ostream& operator << (ostream& cout, Perm& a) {
//		cout << '(';
		FOR(i,1,n) cout << a.x[i] << ' ';
//		cout << ')';
		return cout;
	}
} base[MN], comp[MN], I;
int nBase, nComp;

Perm operator * (const Perm& a, const Perm& b) {
	Perm res;
	FOR(i,1,n)
		res.x[i] = a.x[ b.x[i] ];
	return res;
}
Perm power(Perm a, int k) {
	Perm res = I;
	while (k > 0) {
		if (k & 1) res = res * a;
		k >>= 1;
		a = a * a;
	}
	return res;
}

void init() {
	FOR(i,1,n) I.x[i] = i;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		init();
		// base
		cin >> nBase;
//		cout << "Base: " << endl;
		FOR(i,1,nBase) {
			int l; cin >> l;
			vector<int> a; a.resize(l);
			REP(j,l) cin >> a[j];

			base[i] = I;
			int last = base[i].x[ a.back() ];

			FORD(j,l-1,1) base[i].x[ a[j] ] = base[i].x[ a[j-1] ];
			base[i].x[a[0]] = last;

//			cout << base[i] << endl;
		}
		cin >> nComp;
//		cout << "Comp: " << endl;
		FOR(i,1,nComp) {
			comp[i] = I;
			int l; cin >> l;
			FOR(j,1,l) {
				int u, p; cin >> u >> p;
				comp[i] = comp[i] * power(base[u], p);
			}
//			cout << comp[i] << endl;
		}
		int q; cin >> q;
		FOR(i,1,q) {
			Perm cur = I;
			int l; cin >> l;
			FOR(j,1,l) {
				int u, p; cin >> u >> p;
				cur = cur * power(comp[u], p);
			}
			cout << cur << endl;
		}
	}
}
