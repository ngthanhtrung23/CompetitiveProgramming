
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

int a[111][111];

int main() {
    ios :: sync_with_stdio(false);
    int k;
    while (cin >> k) {
        memset(a, 0, sizeof a);

        int cur = 0;
        FOR(j,2,100) FOR(i,1,j-1) {
            int add = 0;
            FOR(k,1,100) if (k != i && k != j)
                if (a[i][k] && a[k][j]) ++add;

            if (cur + add <= k) {
                a[i][j] = a[j][i] = 1;
                cur += add;
            }
        }

        cout << 100 << endl;
        FOR(i,1,100) {
            FOR(j,1,100) cout << a[i][j];
            cout << endl;
        }
    }
    return 0;
}
