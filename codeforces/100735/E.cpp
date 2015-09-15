
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
using namespace std;

int n;
ll a[111][111], row[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        ll sum = 0;
        memset(row, 0, sizeof row);
        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];
            sum += a[i][j];

            row[i] += a[i][j];
        }
        ll each = sum / (n-1);

        FOR(i,1,n) {
            a[i][i] = each - row[i];
        }

        FOR(i,1,n) {
            FOR(j,1,n) cout << a[i][j] << ' ';
            cout << endl;
        }
    }
}

