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

const int MN = 2011;
const int MOD = 1000000007;
int f[2][MN][MN];

void update(int& x, int val) {
    x = (x + val) % MOD;
    assert(x >= 0);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        string s; cin >> s; REP(i,s.length()) if (s[i] == '-') s[i] = ' ';
        istringstream ss(s);
        int a, b; ss >> a >> b;

        memset(f, 0, sizeof f);
        REP(turn,2) {
            f[turn][0][0] = 1;
            FOR(i,0,a) FOR(j,0,b) REP(add,2) {
                int ii = i, jj = j;
                if (add == 0) ii++;
                else jj++;

                if (ii <= a && jj <= b) {
                    if (turn == 0 && ii > jj) {
                        update(f[turn][ii][jj], f[turn][i][j]);
                    }
                    if (turn == 1) 
                    if (ii <= jj || jj == b) {
                        update(f[turn][ii][jj], f[turn][i][j]);
                    }
                }
            }
        }
        cout << "Case #" << test << ": " << f[0][a][b] << ' ' << f[1][a][b] << endl;
    }
    return 0;
}

