
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
int n, a[MN], f[MN][MN], tr[MN][MN];

void update(int i, int rem, int val, int prev) {
    if (f[i][rem] > val) {
        f[i][rem] = val;
        tr[i][rem] = prev;
    }
}

void trace(int n, int rem) {
    if (n == 1) return ;

    int prev = tr[n][rem];
    int x = n, y = n-1, z = prev;

    trace(n-2, prev);

    if (rem == x) cout << y << ' ' << z << endl;
    else if (rem == y) cout << x << ' ' << z << endl;
    else if (rem == z) cout << x << ' ' << y << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        if (n == 1) {
            cout << a[1] << endl;
            cout << 1 << endl;
            continue;
        }
        else if (n == 2) {
            cout << max(a[1], a[2]) << endl;
            cout << 1 << ' ' << 2 << endl;
            continue;
        }

        FOR(i,1,n) FOR(j,1,i) f[i][j] = 1000111000;

        f[3][1] = max(a[2], a[3]); tr[3][1] = 1;
        f[3][2] = max(a[1], a[3]); tr[3][2] = 1;
        f[3][3] = max(a[1], a[2]); tr[3][3] = 1;
        for(int i = 3; i < n; i += 2) FOR(rem,1,i) {
            int x = rem, y = i+1, z = i+2;
            update(i+2, x, f[i][rem] + max(a[y], a[z]), rem);
            update(i+2, y, f[i][rem] + max(a[z], a[x]), rem);
            update(i+2, z, f[i][rem] + max(a[x], a[y]), rem);
        }
        if (n % 2 == 0) {
            int best = 1000111000;
            FOR(rem,1,n-1) best = min(best, f[n-1][rem] + max(a[rem], a[n]));

            cout << best << endl;
            FOR(rem,1,n) if (f[n-1][rem] + max(a[rem], a[n]) == best) {
                trace(n-1, rem);
                cout << rem << ' ' << n << endl;
                break;
            }
        }
        else {
            int best = 1000111000;
            FOR(rem,1,n) best = min(best, f[n][rem] + a[rem]);
            cout << best << endl;
            FOR(rem,1,n) if (f[n][rem] + a[rem] == best) {
                trace(n, rem);
                cout << rem << endl;
                break;
            }
        }
    }
    return 0;
}

