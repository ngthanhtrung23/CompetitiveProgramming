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

string s;
const int MN = 5011;

int a[MN], sign[MN], nextPlus[MN], prevPlus[MN];
int n;
long long f[MN][MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        memset(f, 0, sizeof f);

        n = 0;
        for(int i = 0; i < s.length(); i += 2) {
            ++n;
            a[n] = s[i] - '0';
            if (i+1 < s.length()) {
                if (s[i+1] == '+') sign[n] = 0;
                else sign[n] = 1;
            }
        }
//        PR(a, n);
//        PR(sign, n-1);

        nextPlus[n] = n;
        FORD(i,n-1,1) {
            if (sign[i] == 0) nextPlus[i] = i;
            else nextPlus[i] = nextPlus[i+1];
        }

        prevPlus[1] = 0;
        FOR(i,2,n) {
            if (sign[i-1] == 0) prevPlus[i] = i-1;
            else prevPlus[i] = prevPlus[i-1];
        }
//        PR(nextPlus, n);
//        PR(prevPlus, n);

        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) f[i][i] = a[i];
            else {
                int k = nextPlus[i];
                if (k >= j) f[i][j] = a[i] * f[i+1][j];
                else f[i][j] = f[i][k] + f[k+1][j];
            }
        }
//        FOR(i,1,n) PR(f[i], n);

        long long res = f[1][n];
        FOR(i,1,n) FOR(j,i,n) {
            long long mid = f[i][j];

            int l = prevPlus[i];
            int r = nextPlus[j];

            if (l+1 <= i-1) mid *= f[l+1][i-1];
            if (j+1 <= r)   mid *= f[j+1][r];

            res = max(res, f[1][l] + mid + f[r+1][n]);
        }
        cout << res << endl;
    }
    return 0;
}

