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

const int MN = 4011;
pair<int,int> a[MN];
int f[MN][MN];
vector<int> at[MN];
int c[MN];

void trace(int i, int j) {
    if (i > j) return ;
    if (f[i][j] == 0) return ;

    int good = 0;
    for(auto id : at[i]) {
        if (a[id].second == j) {
            cout << id << ' ';
            good = 1;
        }
    }
    
    if (f[i][j] == f[i][j-1] + good) trace(i, j-1);
    else if (f[i][j] == f[i+1][j] + good) trace(i+1, j);
    else {
        for(auto id : at[i]) {
            if (f[i][j] == good + f[i][a[id].second] + f[a[id].second][j]) {
                trace(i, a[id].second);
                trace(a[id].second, j);
                return ;
            }
        }
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            int c, r; scanf("%d%d", &c, &r);
            a[i] = make_pair(c - r, c + r);
        }
        int nc = 0;
        FOR(i,1,n) {
            c[++nc] = a[i].first;
            c[++nc] = a[i].second;
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) {
            a[i].first = lower_bound(c+1, c+nc+1, a[i].first) - c;
            a[i].second = lower_bound(c+1, c+nc+1, a[i].second) - c;
        }
//        FOR(i,1,n) cout << a[i].first << ' ' << a[i].second << endl;
        memset(f, 0, sizeof f);
        FOR(i,1,nc) at[i].clear();
        FOR(i,1,n) at[a[i].first].push_back(i);

        FORD(i,nc,1) FOR(j,i,nc) {
            f[i][j] = max(f[i][j-1], f[i+1][j]);
            int good = 0;
            for(auto id : at[i]) {
                if (a[id].second == j) {
                    good = 1;
                }
                else {
                    f[i][j] = max(f[i][j], f[i][a[id].second] + f[a[id].second][j]);
                }
            }
            f[i][j] += good;
        }
        cout << f[1][nc] << endl;
        trace(1, nc);
        cout << endl;
    }
    return 0;
}
