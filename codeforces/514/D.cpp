
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

int n, m, can;
int a[100111][7], save[7];
multiset<int> all[7];

int get() {
    int res = 0;
    FOR(t,1,m) if (!all[t].empty()) res += *all[t].rbegin();
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m >> can) {
        FOR(i,1,n) FOR(j,1,m) cin >> a[i][j];
        FOR(t,1,m) all[t].clear();
        int j = 1;
        int best = -1;
        FOR(i,1,n) {
            FOR(t,1,m) all[t].insert(a[i][t]);
            int sum = get();
            while (sum > can) {
                FOR(t,1,m) all[t].erase(all[t].find(a[j][t]));
                ++j;
                sum = get();
            }
            if (i - j > best) {
                best = i - j;
                FOR(t,1,m) if (!all[t].empty()) save[t] = *all[t].rbegin();
            }
        }
        FOR(t,1,m) cout << save[t] << ' '; cout << endl;
    }
    return 0;
}
