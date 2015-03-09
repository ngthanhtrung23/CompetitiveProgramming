
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

int m, n;
char a[111][10111];
vector<int> ones[111];

bool bad() {
    FOR(i,1,m) {
        bool hasOne = false;
        ones[i].clear();
        FOR(j,1,n) if (a[i][j] == '1') {
            hasOne = true;
            ones[i].push_back(j);
            ones[i].push_back(n+j);
            ones[i].push_back(n+n+j);
        }
        sort(ones[i].begin(), ones[i].end());
        if (!hasOne) return true;
    }
    return false;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        if (bad()) cout << -1 << endl;
        else {
            int res = 1000111000;
            FOR(j,1,n) {
                int cur = 0;
                FOR(i,1,m) {
                    auto it = lower_bound(ones[i].begin(), ones[i].end(), n+j);
                    int x = *it;
                    --it;
                    int y = *it;
                    cur += min(abs(x - (n+j)), abs(y - (n+j)));
                }
                res = min(res, cur);
            }
            cout << res << endl;
        }
    }
    return 0;
}

