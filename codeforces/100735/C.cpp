
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

int m, n;
char a[33][33];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool bad(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n || a[u][v] == 'X';
}

int d[33][33][33][33];

void solve() {
    queue<int> qu1, qv1, qu2, qv2;
    int u1, v1, u2, v2;
    FOR(i,1,m) FOR(j,1,n) {
        if (a[i][j] == 'A') u1 = i, v1 = j;
        if (a[i][j] == 'G') u2 = i, v2 = j;
    }
    memset(d, -1, sizeof d);
    qu1.push(u1);
    qv1.push(v1);
    qu2.push(u2);
    qv2.push(v2);

    d[u1][v1][u2][v2] = 0;

    while (!qu1.empty()) {
        u1 = qu1.front(); qu1.pop();
        v1 = qv1.front(); qv1.pop();
        u2 = qu2.front(); qu2.pop();
        v2 = qv2.front(); qv2.pop();

        if (a[u1][v1] == 'P') {
            cout << d[u1][v1][u2][v2] << endl;
            return ;
        }

        REP(dir,4) {
            int new_u1 = u1 + di[dir];
            int new_v1 = v1 + dj[dir];
            if (bad(new_u1, new_v1)) continue;

            int new_u2 = u2, new_v2 = v2;

            if (new_v2 < new_v1 && !bad(new_u2, new_v2+1)) ++new_v2;
            else if (new_v2 > new_v1 && !bad(new_u2, new_v2-1)) --new_v2;
            else if (new_u2 > new_u1 && !bad(new_u2-1, new_v2)) --new_u2;
            else if (new_u2 < new_u1 && !bad(new_u2+1, new_v2)) ++new_u2;

            if (new_u1 == new_u2 && new_v1 == new_v2) continue;
            if (d[new_u1][new_v1][new_u2][new_v2] >= 0) continue;

            d[new_u1][new_v1][new_u2][new_v2] = d[u1][v1][u2][v2] + 1;
            qu1.push(new_u1);
            qv1.push(new_v1);
            qu2.push(new_u2);
            qv2.push(new_v2);
        }
    }
    cout << -1 << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        solve();
    }
}
