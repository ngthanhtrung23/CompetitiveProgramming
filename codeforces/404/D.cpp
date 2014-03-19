#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1000111;
const int MOD = 1000000007;

char tmp[MN];
string s, alpha = "012*";
int f[MN][2][3], n;

void add(int &a, int x) {
    a += x;
    if (a >= MOD) a -= MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    while (gets(tmp)) {
        n = strlen(tmp);
        memset(f, 0, sizeof f);

        s = " " + string(tmp);
        f[0][0][2] = 1;
        FOR(i,0,n-1) FOR(k,0,1) FOR(t,0,2)
        if (f[i][k][t])
            REP(next,alpha.size())
            if (s[i+1] == alpha[next] || s[i+1] == '?') {
                if (alpha[next] == '0') {
                    if (k == 0 && t != 1)
                        add(f[i+1][0][0], f[i][k][t]);
                }
                else if (alpha[next] == '1') {
                    if (k == 0 && t != 1)
                        add(f[i+1][0][1], f[i][k][t]);
                    if (k == 1 && t != 1)
                        add(f[i+1][0][0], f[i][k][t]);
                }
                else if (alpha[next] == '2') {
                    if (k == 1 && t != 1)
                        add(f[i+1][0][1], f[i][k][t]);
                }
                else if (alpha[next] == '*') {
                    if (t != 0)
                        add(f[i+1][1][2], f[i][k][t]);
                }
            }

        int res = 0;
        FOR(t,0,2) FOR(k,0,1)
        if (t != 1 && f[n][k][t]) {
            add(res, f[n][k][t]);
        }
        cout << res << endl;
    }
    return 0;
}
