
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

const int MN = 55;

int n, win[55][55];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int pair = n * (n-1) / 2;
        memset(win, -1, sizeof win);
        FOR(i,1,pair-1) {
            int u, v; cin >> u >> v;
            win[u][v] = 1;
            win[v][u] = 0;
        }
        FOR(i,1,n) FOR(j,i+1,n) if (win[i][j] < 0) {
            FOR(k,1,n) if (k != i && k != j && win[i][k] == win[k][j]) {
                win[i][j] = win[i][k];
                break;
            }
            if (win[i][j]) cout << i << ' ' << j << endl;
            else cout << j << ' ' << i << endl;
        }
    }
}
