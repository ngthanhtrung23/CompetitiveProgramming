
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

char a[111][111];
int m, n;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    while (cin >> m >> n) {
        int res = 0;
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'P') {
            REP(dir,4) {
                if (a[i+di[dir]][j+dj[dir]] == 'W') {
                    res++;
                    a[i+di[dir]][j+dj[dir]] = ' ';
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

