
#include <bits/stdc++.h>
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

const int MN = 55;
const int MOD = 1e9 + 7;
int f[55][55][22][30], len[55], n;
string s[55];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> s[i];
            len[i] = SZ(s[i]);

            s[i] = " " + s[i] + " ";
        }

        memset(f, 0, sizeof f);
        FORD(i1,n,1) FOR(i2,i1,n) FORD(j,20,0) FORD(x,'z','a') {
            int ix = x - 'a';
            int& res = f[i1][i2][j][ix];
            res = 0;

            if (i1 == i2) {
                if (len[i1] == j) {
                    res = 1;
                    continue;
                }

                if (s[i1][j+1] == '?') {
                    res = ('z' - x + 1LL) * f[i1][i2][j+1][0] % MOD;
                    continue;
                }
                else {
                    if (s[i1][j+1] >= x) {
                        res = f[i1][i2][j+1][0];
                        continue;
                    }
                }
            }

            // some string is too short
            int bad = 0;
            FOR(i,i1+1,i2) if (len[i] <= j) bad = 1;
            if (bad) continue;

            // first string too short
            if (len[i1] == j) {
                res = f[i1+1][i2][j][ix];
                continue;
            }

            FOR(i,i1,i2) if (s[i][j+1] != '?' && s[i][j+1] < x) bad = 1;
            if (bad) continue;
            
            // normal case
            res = 0;
            FOR(cur,x,'z') {
                FOR(mid,i1,i2) {
                    if (s[mid][j+1] != '?' && s[mid][j+1] != cur) break;

                    if (mid == i2) {
                        res = res + f[i1][i2][j+1][0];
                        if (res >= MOD) res -= MOD;
                    }
                    else {
                        if (cur == 'z') continue;
                        res = (res + f[i1][mid][j+1][0] * (ll) f[mid+1][i2][j][cur + 1 - 'a']) % MOD;
                    }
                }
            }
        }
        cout << f[1][n][0][0] << endl;
    }
}
