#include<bits/stdc++.h>
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

const int N = 100000;
ll f[N + 11][40];

int main() {
    freopen("peaks.in", "r", stdin);
    freopen("peaks.out", "w", stdout);
	f[1][1] = 1;
	
	for(int i=2; i<=N; i++) {
		f[i][1] = (2*f[i-1][1]) % 239;	
	}	
	
	for(int j=2; j<=30; j++) {
		for(int i=1; i<=N; i++)
            f[i][j] = (2*j*f[i-1][j] + (i-2*j+2)*f[i-1][j-1]) % 239;
	}
    long long n, k;
    while (cin >> n >> k) {
        n = n % 56882;
        while (n + 56882 < N) n += 56882;
        cout << f[n][k] << endl;
    }
    return 0;
    FOR(j,1,30) {
        FOR(cycle,1,100000) {
            bool good = true;
            FORD(i,N,N-cycle*10) {
                if (i < 0) assert(false);

                if (f[i][j] != f[i-cycle][j]) {
                    good = false;
                    break;
                }
            }
            if (good) {
                cout << j << ' ' << cycle << endl;
                break;
            }
        }
    }
}
