
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 200111;
const int ZERO = 100000;

vector<int> values[MN];
vector< pair<int,int> > pts[MN];
int n, x[MN], y[MN];
map< pair<int,int>, int > assigned;
int w[MN];
pair<int,int> res[MN];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);

	while (scanf("%d", &n) == 1) {
		REP(i,MN) {
			values[i].clear();
			pts[i].clear();
		}
		assigned.clear();
		FOR(i,1,n) {
			scanf("%d%d", &x[i], &y[i]);
			pts[y[i] - x[i] + ZERO].push_back(make_pair(x[i], y[i]));
		}
		FOR(i,1,n) {
			scanf("%d", &w[i]);
			values[w[i] + ZERO].push_back(i);
		}
		try {
			REP(diff,MN) {
				if (pts[diff].size() != values[diff].size()) throw 1;

				sort(pts[diff].begin(), pts[diff].end());
				sort(values[diff].begin(), values[diff].end());

				REP(i,pts[diff].size()) {
					res[ values[diff][i] ] = pts[diff][i];
					assigned[ pts[diff][i] ] = values[diff][i];
				}
			}
			FOR(i,1,n) {
				pair<int,int> cur = make_pair(x[i], y[i]);
				pair<int,int> up = make_pair(x[i], y[i] + 1);
				pair<int,int> right = make_pair(x[i] + 1, y[i]);

				if (assigned.count(up) && assigned[up] < assigned[cur]) throw 2;
				if (assigned.count(right) && assigned[right] < assigned[cur]) throw 3;
			}
			puts("YES");
			FOR(i,1,n) printf("%d %d\n", res[i].first, res[i].second);
		} catch (int e) {
			puts("NO");
		}
	}
}
