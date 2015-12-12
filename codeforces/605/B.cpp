
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

const int MN = 100111;
struct Edge {
	int u, v;
	int w, id;
	int good;
} edges[MN];

bool cmpW(const Edge& a, const Edge& b) {
	if (a.w == b.w) return a.good > b.good;
	return a.w < b.w;
}
bool cmpId(const Edge& a, const Edge& b) {
	return a.id < b.id;
}
int n, m;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n >> m) {
		FOR(i,1,m) {
			cin >> edges[i].w >> edges[i].good;
			edges[i].id = i;
		}
		sort(edges+1, edges+m+1, cmpW);
		int cur = 1;
		try {
			int uu = 1, vv = 3;

			FOR(i,1,m)
			if (edges[i].good) {
				edges[i].u = cur;
				edges[i].v = cur + 1;
				++cur;
			}
			else {
				if (vv > cur) throw 1;
				edges[i].u = uu;
				edges[i].v = vv;

				++uu;
				if (uu == vv-1) {
					uu = 1;
					++vv;
				}
			}

			sort(edges+1, edges+m+1, cmpId);
			FOR(i,1,m) cout << edges[i].u << ' ' << edges[i].v << '\n';
		} catch (int e) {
			cout << -1 << endl;
		}
	}
}
