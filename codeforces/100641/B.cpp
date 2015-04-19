
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

const int MN = 511;

string s;
#define equal ____equal
int f[MN][MN], equal[MN][MN];
bool good[MN][MN][MN];
int n;

int getlen(int x) {
    int res = 0;
    while (x) {
        res++;
        x /= 10;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> s && s != "0") {
        n = s.length();
        s = " " + s;

        memset(equal, 0, sizeof equal);
        FORD(i,n,1) FORD(j,n,i+1) {
            if (s[i] != s[j]) equal[i][j] = 0;
            else equal[i][j] = equal[i+1][j+1] + 1;
        }
        FORD(i,n,1) FOR(j,i,n) {
            FOR(k,i,j) {
                int l_ik = k - i + 1;
                if (k == j) good[i][j][k] = true;
                else if ((j - i + 1) % l_ik) good[i][j][k] = false;
                else good[i][j][k] = good[i][j-l_ik][k] && equal[i][j-l_ik+1] >= l_ik;
            }
        }
        FORD(i,n,1) FOR(j,i,n) {
            f[i][j] = j - i + 1;
            FOR(k,i,j-1) {
                f[i][j] = min(f[i][j], f[i][k] + f[k+1][j]);
                if (good[i][j][k]) {
                    if (i == k) f[i][j] = min(f[i][j], f[i][k] + getlen((j - i + 1) / (k - i + 1)));
                    else f[i][j] = min(f[i][j], 2 + f[i][k] + getlen((j - i + 1) / (k - i + 1)));
                }
            }
        }
        cout << "Case " << ++test << ": " << f[1][n] << '\n';
    }
    return 0;
}
