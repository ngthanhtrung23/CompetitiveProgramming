
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int d[22][22], balance[22];
bool visited[TWO(20)];

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        int n; scanf("%d", &n);
        REP(i,n) REP(j,n) scanf("%d", &d[i][j]);

        queue<int> qu;
        memset(visited, 0, sizeof visited);
        qu.push(TWO(n) - 1);
        visited[TWO(n) - 1] = true;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            REP(i,n) if (CONTAIN(u,i)) {
                balance[i] = 0;
                REP(j,n) if (CONTAIN(u,j))
                    balance[i] -= d[i][j];

                if (balance[i] < 0 && !visited[u - TWO(i)]) {
                    visited[u - TWO(i)] = true;
                    qu.push(u - TWO(i));
                }
            }
        }
        bool ok = false;
        REP(i,n) if (visited[TWO(i)]) {
            ok = true;
            printf("%d ", i+1);
        }
        if (!ok) puts("0");
        else puts("");
    }
    return 0;
}
