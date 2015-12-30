
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 5011;
const int MOD = 1e9 + 7;

#define equal equal__
int f[MN][MN], equal[MN][MN];
string s;
int n;

bool isLower(int u, int v, int len) {
    if (equal[u][v] >= len) {
        return false;
    }
    else {
        return s[u+equal[u][v]] < s[v+equal[u][v]];
    }
}

void add(int& x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        cin >> s;
        s = " " + s;
        FORD(j,n,1) FORD(i,j,1) {
            if (i == j) equal[i][j] = n - i + 1;
            else {
                if (s[i] != s[j]) equal[i][j] = 0;
                else equal[i][j] = equal[i+1][j+1] + 1;
            }
        }
        memset(f, 0, sizeof f);
        FOR(i,1,n) {
            f[i][0] = 0;
            FOR(len,1,n) {
                f[i][len] = f[i][len-1];
                if (len > i) continue;
                if (len == i) {
                    add(f[i][len], 1);
                }

                int j = i - len;

                if (s[j+1] == '0') {
                    continue;
                }

                if (j >= len && isLower(j-len+1, i-len+1, len)) {
                    add(f[i][len], f[j][len]);
                }
                else {
                    add(f[i][len], f[j][len-1]);
                }
            }
        }
        cout << f[n][n] << endl;
    }
}
