#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

int m, n; char a[111][111];
int visited[111][111];

int solve() {
    int u, v;
	memset(visited, 0, sizeof visited);
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'P') {
        u = i;
        v = j;
		visited[u][v] = 1;
    }

    while (true) {
        if (u == m) return v;

		++u;
		if (a[u][v] == '/') {
			--v;
			if (a[u][v] == '\\') return -1;
		}
		if (a[u][v] == '\\') {
			++v;
			if (a[u][v] == '/') return -1;
		}
		
		if (v < 1 || v > n) return -1;
		if (visited[u][v]) return -1;
		
		visited[u][v] = 1;
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        cout << solve() << endl;
    }
}
