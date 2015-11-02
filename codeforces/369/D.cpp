
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

const int MN = 3011;

int visited[MN][MN];
int n, k, p[MN];
int hasPositive[MN], noPerfect[MN];

queue<int> qu;
queue<int> qv;
void go(int u, int v, int l) {
    if (visited[u][v] < 0) {
        visited[u][v] = l + 1;
        qu.push(u);
        qv.push(v);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) {
            cin >> p[i];
        }

        hasPositive[n+1] = 0;
        FORD(i,n,1) {
            if (p[i] == 0) hasPositive[i] = hasPositive[i+1];
            else hasPositive[i] = 1;
        }
        noPerfect[n+1] = 1;
        FORD(i,n,1) {
            if (p[i] == 100) noPerfect[i] = 0;
            else noPerfect[i] = noPerfect[i+1];
        }

        memset(visited, -1, sizeof visited);
        visited[1][2] = 0;
        qu.push(1);
        qv.push(2);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            int v = qv.front(); qv.pop();

            // 1. u killed, v survived
            if (u <= n && p[u] < 100 && hasPositive[v]) {
                go(v, v + 1, visited[u][v]);
            }
            // 2. u survived, v killed
            if (v <= n && p[u] > 0 && noPerfect[v]) {
                go(u, v+1, visited[u][v]);
            }
            // 3. u killed, v killed
            if (v <= n && p[u] > 0 && hasPositive[v]) {
                go(v+1, v+2, visited[u][v]);
            }
        }
        int res = 0;
        FOR(i,1,n+2) FOR(j,i+1,n+2) if (0 <= visited[i][j] && visited[i][j] <= k) ++res;
        cout << res << endl;
    }
}
