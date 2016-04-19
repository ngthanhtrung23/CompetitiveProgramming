
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

int res[1000111], f, r;

#undef int
int main() {
#define int long long
//    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
	int n, h;
	while (cin >> n >> h) {
		f = 500111;
		r = f - 1;

		FOR(t,1,100111) {
			int last = t * t;

			if (t == h+1) {
				if (last <= n)
					res[--f] = last;
			}
			else if (t > h+1) {
				int left = sqr(t - 1) + h + 1;
				if (left <= n) res[--f] = left;

				int right = sqr(t - 1) + t + h;
				if (right <= n) res[++r] = right;
			}
		}

		FOR(i,f,r) printf("%lld ", res[i]);
		puts("");
		fflush(stdout);
	}
}
