
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

int f[33][33][55];

int get(int m, int n, int k) {
    if (k > m*n) return 1000111000;
    if (k == 0) return 0;
    if (k == m*n) return 0;
    if (f[m][n][k] >= 0) return f[m][n][k];
    
    int res = 1e9;
    // cut vertically
    FOR(x,1,n-1)
        FOR(k1,0,k) {
            res = min(res,
                    get(m, x, k1) + get(m, n-x, k-k1) + m*m);
        }

    // cut horizontally
    FOR(x,1,m-1)
        FOR(k1,0,k) {
            res = min(res,
                    get(x, n, k1) + get(m-x, n, k-k1) + n*n);
        }

    return f[m][n][k] = res;
}

int main() {
    ios :: sync_with_stdio(false);
    memset(f, -1, sizeof f);
//    FOR(i,1,30) FOR(j,1,30) {
//        FOR(k,1,50) {
//            cout << get(i,j,k) << ',';
//        }
//        cerr << i << ' ' << j << endl;
//    }
//    return 0;
    int ntest; cin >> ntest;
    while (ntest--) {
        int m, n, k; cin >> m >> n >> k;
        cout << get(m, n, k) << '\n';
    }
}
