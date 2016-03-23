#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 211;

int m, n, k;
int p[MN][MN], priority[MN];
pair<int,int> order[MN];
char res[MN];
int f[MN][MN];

const int INF = 1000111000111000111LL;

int solve() {
    memset(f, 0, sizeof f);

    f[0][0] = 1;
    FOR(i,0,n-1) FOR(s,0,i) {
        int t = f[i][s]; if (!t) continue;
        if (t > INF) t = f[i][s] = INF;

        if (res[i+1] == '(') {
            f[i+1][s+1] += t;
        }
        else if (res[i+1] == ')') {
            if (s) {
                f[i+1][s-1] += t;
            }
        }
        else {
            f[i+1][s+1] += t;
            if (s)
                f[i+1][s-1] += t;
        }
    }
    return f[n][0];
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n >> k) {
        int savem = m, saven = n;

        FOR(i,1,m+n-1) priority[i] = MN * MN;
        FOR(i,1,m) FOR(j,1,n) {
            cin >> p[i][j];
            int s = i + j - 1;
            priority[s] = min(priority[s], p[i][j]);
        }

        n = m + n - 1;
        FOR(i,1,n) order[i] = make_pair(priority[i], i);
        sort(order+1, order+n+1);

        memset(res, 0, sizeof res);
        FOR(i,1,n) {
            int pos = order[i].second;
            // open bracket
            res[pos] = '(';
            int cur = solve();

            if (cur >= k) continue;

            res[pos] = ')';
            k -= cur;
        }
        FOR(i,1,savem) {
            FOR(j,1,saven) cout << res[i+j-1];
            cout << '\n';
        }
    }
}
