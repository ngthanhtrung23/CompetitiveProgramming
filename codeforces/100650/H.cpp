
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

const int MN = 1011;
int n, a[MN], f[2][MN][MN];

int get(int turn, int i, int j) {
    if (i > j) return 0;
    if (f[turn][i][j] >= 0) return f[turn][i][j];

    if (turn == 0) {
        return f[turn][i][j] = max(get(1, i+1, j) + a[i], get(1, i, j-1) + a[j]);
    }
    else {
        if (a[i] >= a[j]) {
            return f[turn][i][j] = get(1-turn, i+1, j) - a[i];
        }
        else return f[turn][i][j] = get(1-turn, i, j-1) - a[j];
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n && n) {
        FOR(i,1,n) cin >> a[i];

        memset(f, -1, sizeof f);
        cout << "In game " << ++test << ", the greedy strategy might lose by as many as "
            << get(0, 1, n) << " points.\n";
    }
    return 0;
}

