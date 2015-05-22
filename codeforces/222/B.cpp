
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

int a[MN][MN], m, n, k, orig_row[MN], orig_col[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d%d\n", &m, &n, &k) == 3) {
        FOR(i,1,m) FOR(j,1,n) scanf("%d", &a[i][j]);
        scanf("\n");
        FOR(i,1,m) orig_row[i] = i;
        FOR(j,1,n) orig_col[j] = j;

        while (k--) {
            char typ; int u, v; scanf("%c%d%d\n", &typ, &u, &v);
            if (typ == 'c') {
                swap(orig_col[u], orig_col[v]);
            } else if (typ == 'r') {
                swap(orig_row[u], orig_row[v]);
            } else {
                printf("%d\n", a[orig_row[u]][orig_col[v]]);
            }
        }
    }
    return 0;
}

