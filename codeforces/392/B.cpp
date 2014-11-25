#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

long long cost[5][5];
long long f[44][5][5];

void update(long long &x, long long val) { x = min(x, val); }

long long get(int n, int a, int b) {
    if (n == 0) return 0;
    if (f[n][a][b] >= 0) return f[n][a][b];

    int c = 6 - a - b;
    f[n][a][b] = 1000111000111000111LL;
    update(f[n][a][b], get(n-1, a, c) + cost[a][b] + min(get(n-1, c, b), get(n-1, c, a) + get(n-1, a, b)));
    update(f[n][a][b], get(n-1, a, b) + cost[a][c] + min(get(n-1, b, a), get(n-1, b, c) + get(n-1, c, a))
                + cost[c][b] + min(get(n-1, a, b), get(n-1, a, c) + get(n-1, a, b)));
    return f[n][a][b];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> cost[1][1]) {
        FOR(i,1,3) FOR(j,1,3) if (i > 1 || j > 1) cin >> cost[i][j];

        int n; cin >> n;
        memset(f, -1, sizeof f);
        cout << get(n, 1, 3) << endl;
    }
    return 0;
}
