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
using namespace std;

ll a[111][111];
int cnt[111];

int main() {
    ios :: sync_with_stdio(false);
    int nCand, nCity;
    while (cin >> nCand >> nCity) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,nCity) {
            int winner = 1;
            FOR(j,1,nCand) {
                cin >> a[i][j];
                if (a[i][j] > a[i][winner]) winner = j;
            }
            ++cnt[winner];
        }
        int res = 1;
        FOR(i,1,nCand) if (cnt[i] > cnt[res]) res = i;
        cout << res << endl;
    }
}
