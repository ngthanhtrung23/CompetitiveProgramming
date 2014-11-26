#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int m, n;
string a[1000111];
string res[1011][1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        int k = 0;
        FOR(i,1,m) FOR(j,1,n) {
            ++k;
            cin >> a[k];
            if (a[k] == "10") a[k] = "01";
        }
        sort(a+1, a+k+1);
        reverse(a+1, a+k+1);

        k = 0;
        FOR(i,1,m) {
            if (i % 2 == 1) {
                FOR(j,1,n) {
                    ++k;
                    if (a[k] == "01" && res[i-1][j] == "01") res[i][j] = "10";
                    else res[i][j] = a[k];
                }
            }
            else {
                FORD(j,n,1) {
                    ++k;
                    if (a[k] == "01" && res[i-1][j] == "01") res[i][j] = "10";
                    else res[i][j] = a[k];
                }
            }
        }
        FOR(i,1,m) {
            FOR(j,1,n) cout << res[i][j] << ' ';
            cout << endl;
        }
    }
    return 0;
}
