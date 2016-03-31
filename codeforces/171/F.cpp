
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

int sieve[1000111];

int rev(int x) {
    int res = 0;
    while (x) {
        res = (res * 10) + x % 10;
        x /= 10;
    }
    return res;
}

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        int j = i*i;
        while (j <= 1000000) {
            sieve[j] = 1;
            j += i;
        }
    }
    sieve[1] = 1;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
	int n;
	vector<int> res;
	init();
	FOR(i,2,1000000) if (!sieve[i] && !sieve[rev(i)] && rev(i) != i) {
		res.push_back(i);
	}
	while (cin >> n) {
		cout << res[n-1] << endl;
	}
}
