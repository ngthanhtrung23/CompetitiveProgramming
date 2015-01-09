#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define next __next
using namespace std;

const int MN = 5011;

int m, n, next[MN][MN], cnt[MN];
char a[MN][MN];
string tmp;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        FOR(i,1,m) {
            cin >> tmp;
            FOR(j,1,n) a[i][j] = tmp[j-1];

            next[i][n+1] = n+1;
            FORD(j,n,1) {
                if (a[i][j] == '0') next[i][j] = j;
                else next[i][j] = next[i][j+1];
            }
        }

        int res = 0;
        FOR(left,1,n) {
            memset(cnt, 0, sizeof cnt);
            FOR(i,1,m) {
                int right = next[i][left];
                ++cnt[right - left];
            }
            FORD(i,n,1) {
                cnt[i] += cnt[i+1];
                res = max(res, cnt[i] * i);
            }
        }
        cout << res << endl;
    }
    return 0;
}
