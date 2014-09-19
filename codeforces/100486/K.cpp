#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 211;

bool isAncestor[MN][MN], visited[MN];
int vao[MN], a[MN][MN], father[MN];
vector<int> ke[MN];
int n;

void init() {
    memset(isAncestor, false, sizeof isAncestor);
    memset(vao, 0, sizeof vao);
    FOR(i,1,n) ke[i].clear();
    memset(visited, false, sizeof visited);
    memset(father, 0, sizeof father);
}

void addEdge(int u, int v) {
    ke[v].push_back(u);
    vao[u]++;
    isAncestor[u][v] = true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        init();
        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] != i) addEdge(a[i][j], i);
            if (a[i][j] != j) addEdge(a[i][j], j);
        }

        queue<int> qu;
        FOR(i,1,n) if (!vao[i]) {
            visited[i] = true;
            qu.push(i);
        }

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();

            FOR(v,1,n) if (isAncestor[u][v] && !father[v]) {
                father[v] = u;
            }

            REP(i,ke[u].size()) {
                int v = ke[u][i];
                vao[v]--;

                if (!vao[v]) {
                    visited[v] = true;
                    qu.push(v);
                }
            }
        }
        FOR(i,1,n) cout << father[i] << ' ';
        cout << endl;
    }
    return 0;
}
