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

const int MN = 611;
int n, l[MN], r[MN], f[MN][MN], tr[MN][MN];

void trace(int i, int j) {
    if (i == j) cout << "()";
    else {
        int k = tr[i][j];
        if (k == i) {
            cout << "()";
            trace(i+1, j);
        }
        else if (k == j) {
            cout << '(';
            trace(i+1, j);
            cout << ')';
        }
        else {
            cout << '(';
            trace(i+1, k);
            cout << ')';
            trace(k+1, j);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> l[i] >> r[i];
        memset(f, 0, sizeof f);

        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) {
                if (l[i] <= 1 && 1 <= r[i]) f[i][i] = 1;
                else f[i][j] = 0;
            }
            else {
                f[i][j] = 0;
                FOR(a,l[i],r[i])
                if (a % 2 == 1) {
                    int k = (a + i + i - 1) / 2;
                    if (k < i || k > j) continue;

                    if (k == i && f[i+1][j]) {
                        f[i][j] = 1;
                        tr[i][j] = k;
                        break;
                    }
                    if (k == j && f[i+1][j]) {
                        f[i][j] = 1;
                        tr[i][j] = k;
                        break;
                    }
                    if (i < k && k < j && f[i+1][k] && f[k+1][j]) {
                        f[i][j] = 1;
                        tr[i][j] = k;
                        break;
                    }
                }
            }
        }
        if (f[1][n] == 1) trace(1, n);
        else cout << "IMPOSSIBLE";
        cout << endl;
    }
    return 0;
}
