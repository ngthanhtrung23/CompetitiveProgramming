
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int k, n, m, c[1011][1011];
vector<int> ke[1011];

void flipEdge(int u, int v) {
    if (c[u][v]) {
        c[u][v] = c[v][u] = 0;
        --m;
    }
    else {
        c[u][v] = c[u][v] = 1;
        ++m;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> k) {
        if (k % 2 == 0) cout << "NO" << endl;
        else {
            if (k == 1) { cout << "YES\n2 1\n1 2\n"; continue; }
            n = 2 * (k + 2);
            memset(c, 0, sizeof c);
            m = 0;

            flipEdge(n/2, n);
            FOR(i,1,k+1) FOR(j,i+1,k+1) flipEdge(i, j);
            for(int turn = 0, x = 1; turn < (k-1) / 2; ++turn, x += 2) {
                flipEdge(x, x+1);
                flipEdge(x, k+2);
                flipEdge(x+1, k+2);
            }

            FOR(i,n/2+1, n-1) FOR(j,i+1, n-1) flipEdge(i, j);
            for(int turn = 0, x = n/2+1; turn < (k-1) / 2; ++turn, x += 2) {
                flipEdge(x, x+1);
                flipEdge(x, n);
                flipEdge(x+1, n);
            }

            cout << "YES" << endl;
            cout << n << ' ' << m << endl;
            FOR(i,1,n) FOR(j,i+1,n) if (c[i][j]) cout << i << ' ' << j << endl;
        }
    }
    return 0;
}
