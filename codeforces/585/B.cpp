
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

char a[4][511];
int n, k;
int f[4][511];

int main() {
    ios :: sync_with_stdio(false);
    int ntest;
    while (cin >> ntest) {
        while (ntest--) {
            cin >> n >> k;
            memset(f, 0, sizeof f);
            memset(a, '.', sizeof a);
            FOR(row,1,3) FOR(i,1,n) {
                cin >> a[row][i];
                if (a[row][i] == 's') f[row][i] = 1;
            }
            FOR(i,1,n-1) FOR(cur,1,3) if (f[cur][i]) {
                FOR(next,1,3) if (abs(next - cur) <= 1) {
                    int i_now = i*3 - 2;
                    int i_next = i_now + 3;
                    if (a[cur][i_now+1] == '.'
                            && a[next][i_now + 1] == '.'
                            && a[next][i_now + 2] == '.'
                            && a[next][i_next] == '.') f[next][i+1] = 1;
                }
            }
            cout << (f[1][n] + f[2][n] + f[3][n] ? "YES" : "NO") << endl;
        }
    }
}
