#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 55;
const int MOD = 1e9 + 7;
int f[55][55][22][30], len[55], n;
string s[55];

int dp(int i1, int i2, int j, char x) {
    int ix = x - 'a';
    if (f[i1][i2][j][ix] >= 0) return f[i1][i2][j][ix];

    int& res = f[i1][i2][j][ix];

    // only 1 string left
    if (i1 == i2) {
        if (len[i1] == j) return res = 1;

        if (s[i1][j+1] == '?') {
            return res = ('z' - x + 1) * dp(i1, i2, j+1, 'a') % MOD;
        }
        else {
            if (s[i1][j+1] >= x)
                return res = dp(i1, i2, j+1, 'a') % MOD;
            else return res = 0;
        }
    }

    // some string is too short
    FOR(i,i1+1,i2) if (len[i] <= j) return res = 0;

    // first string is too short
    if (len[i1] == j) {
        return res = dp(i1+1, i2, j, x);
    }

    FOR(i,i1,i2) if (s[i][j+1] != '?' && s[i][j+1] < x) return res = 0;
    
    // all is good
    res = 0;
    FOR(mid,i1,i2) {
        if (s[mid][j+1] != '?' && s[mid][j+1] != x) break;

        if (mid == i2) {
            res = (res + dp(i1, i2, j+1, 'a')) % MOD;
        }
        else {
            if (x == 'z') continue;
            res = (res + dp(i1, mid, j+1, 'a') * dp(mid+1, i2, j, x + 1)) % MOD;
        }
    }
    if (x < 'z') {
        res = (res + dp(i1, i2, j, x+1)) % MOD;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> s[i];
            len[i] = SZ(s[i]);

            s[i] = " " + s[i] + " ";
        }

        memset(f, -1, sizeof f);
        cout << dp(1, n, 0, 'a') << endl;
    }
}
