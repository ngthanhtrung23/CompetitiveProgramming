#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

char a[111][111];
int visited[111][111];

int bfs(int startu, int startv) {
    queue< pair<int,int> > qu;
    qu.push({startu, startv});
    
    memset(visited, -1, sizeof visited);
    visited[startu][startv] = 0;

    while (!qu.empty()) {
        auto [u, v] = qu.front(); qu.pop();
        if (a[u][v] == 'B') {
            return visited[u][v];
        }

        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di*di + dj*dj == 1) {
                    int uu = u + di, vv = v + dj;
                    if (a[uu][vv] == '*') continue;
                    if (visited[uu][vv] >= 0) continue;

                    visited[uu][vv] = visited[u][v] + 1;
                    qu.push({uu, vv});
                }
            }
        }
    }
    assert(false);
}

int32_t main() {
    ios::sync_with_stdio(0);
    int nRow, nCol;
    while (cin >> nRow >> nCol) {
        memset(a, '*', sizeof a);

        for (int i = 1; i <= nRow; i++) {
            for (int j = 1; j <= nCol; j++) {
                cin >> a[i][j];
            }
        }

        for (int i = 1; i <= nRow; i++) {
            for (int j = 1; j <= nCol; j++) {
                if (a[i][j] == 'C') {
                    cout << bfs(i, j) << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
