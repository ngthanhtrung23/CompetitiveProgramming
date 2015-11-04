
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

const int MN = 1011;

char a[MN][MN];
int m, n, k;
pair<char,int> x[100111];
int sum[MN][MN];

int getSum(int i1, int j1, int i2, int j2) {
    if (i1 > i2) swap(i1, i2);
    if (j1 > j2) swap(j1, j2);
    return sum[i2][j2] - sum[i1-1][j2] - sum[i2][j1-1] + sum[i1-1][j1-1];
}

bool outside(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n;
}

void init() {
    FOR(i,1,m) FOR(j,1,n) {
        sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        if (a[i][j] == '#') ++sum[i][j];
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        scanf("%d\n", &k);
        FOR(i,1,k) scanf("%c %d\n", &x[i].first, &x[i].second);

        init();

        string res = "";

        FOR(i,1,m) FOR(j,1,n) if (a[i][j] >= 'A' && a[i][j] <= 'Z') {
            try {
                int u = i, v = j;
                FOR(kk,1,k) {
                    char dir = x[kk].first;
                    int len = x[kk].second;

                    int uu = u, vv = v;
                    if (dir == 'N') uu -= len;
                    else if (dir == 'S') uu += len;
                    else if (dir == 'E') vv += len;
                    else if (dir == 'W') vv -= len;
                    else assert(false);

                    if (outside(uu, vv)) throw 1;
                    if (getSum(u, v, uu, vv) > 0) throw 2;

                    u = uu; v = vv;
                }
                res += a[i][j];
            } catch (int e) {
            }
        }
        sort(res.begin(), res.end());
        if (res == "") res = "no solution";
        cout << res << endl;
    }
}
