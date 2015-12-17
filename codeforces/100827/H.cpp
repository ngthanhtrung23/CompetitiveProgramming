
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 5011;

bool visited[MN][MN];
int n, m, s[22];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> m; FOR(i,1,m) cin >> s[i];
        queue<int> qp;
        queue<int> qu;
        memset(visited, 0, sizeof visited);

        visited[0][0] = true;
        qp.push(0);
        qu.push(0);
        while (!qu.empty()) {
            int p = qp.front(); qp.pop();
            int u = qu.front(); qu.pop();

            FOR(i,1,m) {
                int pp = p + s[i];
                int uu = u + pp;

                if (uu > n) continue;

                if (!visited[pp][uu]) {
                    visited[pp][uu] = true;
                    qp.push(pp);
                    qu.push(uu);
                }
            }
        }
        bool found = false;
        FORD(i,n,1) {
            if (visited[i][n]) {
                cout << i << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << -1 << endl;
    }
}
