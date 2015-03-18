
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

const int MN = 311;

int m, n, k;
char a[MN][MN];

vector< tuple<int,int,int> > res;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> k) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        res.clear();
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '*')
            FOR(x,1,min(m,n)) {
                if (i - x < 1 || i + x > m || j - x < 1 || j + x > n) continue;

                if (a[i-x][j] == '*' && a[i+x][j] == '*'
                        && a[i][j-x] == '*' && a[i][j+x] == '*') {
                    res.push_back(make_tuple(x, i, j));
                }
            }
        sort(res.begin(), res.end());
        --k;
        if (k >= res.size()) cout << -1 << endl;
        else {
            int x = get<0>(res[k]);
            int i = get<1>(res[k]);
            int j = get<2>(res[k]);

            cout << i << ' ' << j << endl;
            cout << i - x << ' ' << j << endl;
            cout << i + x << ' ' << j << endl;
            cout << i << ' ' << j - x << endl;
            cout << i << ' ' << j + x << endl;
        }
    }
    return 0;
}
