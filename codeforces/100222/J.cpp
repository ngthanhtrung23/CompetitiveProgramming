
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

string s;
int n;
bool f[511][511][2];
int tr[511][511][2];

void go(int i, int j, int val) {
    if (i == j) {
        putchar(s[i]);
        return ;
    }
    if (tr[i][j][val] == -1) {
        putchar('!');
        putchar('(');
        go(i+1, j, 1 - val);
        putchar(')');
    }
    else {
        int k = tr[i][j][val];
        REP(left,2) REP(right,2)
            if (f[i][k-1][left] && f[k+1][j][right]) {
                int cur = (s[k] == '&') ? (left & right)
                    : (left | right);
                if (cur == val) {
                    putchar('(');
                    go(i, k-1, left);
                    putchar(')');
                    putchar(s[k]);
                    putchar('(');
                    go(k+1, j, right);
                    putchar(')');
                    return ;
                }
            }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);

    while (cin >> s) {
        n = s.length();
        memset(f, 0, sizeof f);
        REP(i,n) if (s[i] == '0' || s[i] == '1') {
            f[i][i][s[i] - '0'] = 1;
        }
        FORD(i,n-1,0) FOR(j,i+1,n-1) {
            if (s[i] == '!') {
                if (f[i+1][j][0]) {
                    f[i][j][1] = true;
                    tr[i][j][1] = -1;
                }
                if (f[i+1][j][1]) {
                    f[i][j][0] = true;
                    tr[i][j][0] = -1;
                }
            }
            FOR(k,i+1,j-1) {
                if (s[k] == '&') {
                    REP(left,2) REP(right,2)
                        if (f[i][k-1][left] && f[k+1][j][right]) {
                            int val = left & right;
                            f[i][j][val] = true;
                            tr[i][j][val] = k;
                        }
                }
                else if (s[k] == '|') {
                    REP(left,2) REP(right,2)
                        if (f[i][k-1][left] && f[k+1][j][right]) {
                            int val = left | right;
                            f[i][j][val] = true;
                            tr[i][j][val] = k;
                        }
                }
            }
        }
        if (f[0][n-1][1]) {
            go(0, n-1, 1);
            puts("");
        }
        else puts("Impossible");
    }
}

