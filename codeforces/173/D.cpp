//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

int n, m, side[MN], visited[MN], res[MN];
vector<int> ke[MN];
vector<int> l1, l2;

void dfs(int u, int color, int &a, int &b) {
    side[u] = color;
    if (color == 0) a++; else b++;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (side[v] < 0) {
            dfs(v, 1-color, a, b);
        }
    }
}

void dfs2(int u) {
    visited[u] = 1;
    side[u] = 1 - side[u];
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (!visited[v]) {
            dfs2(v);
        }
    }
}

void reverse(int u) {
    memset(visited, 0, sizeof visited);
    dfs2(u);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        memset(res, -1, sizeof res);
        FOR(i,1,n) ke[i].clear();
        int u, v;
        while (m--) {
            scanf("%d%d", &u, &v);
            ke[u].PB(v);
            ke[v].PB(u);
        }
        memset(side, -1, sizeof side);
        l1.clear(); l2.clear();
        FOR(i,1,n) if (side[i] < 0) {
            int a = 0, b = 0;
            dfs(i, 0, a, b);
//            cout << i << ' ' << a << ' ' << b << endl;
            if ((a - b + 3) % 3 == 1) l1.PB(i);
            else if ((a - b + 3) % 3 == 2) l2.PB(i);
        }
//        PR(side, n);
        int sum = n;
        FOR(i,1,n) sum -= side[i];
        bool can = true;
        int cur = 1;
        if (sum % 3 == 0) {
        }
        else {
            if (sum % 3 == 2) {
                swap(l1, l2);
                FOR(i,1,n) side[i] = 1 - side[i];
            }
            if (l1.size() > 0) {
                reverse(l1[0]);
            }
            else if (l2.size() > 1) {
                reverse(l2[0]);
                reverse(l2[1]);
            }
            else {
                can = false;
                
                memset(visited, 0, sizeof visited);
                int n1 = 0;
                FOR(i,1,n) if (side[i] == 1) n1++;
                int n0 = n - n1;
                
                FOR(i,1,n) if (side[i] == 0 && ke[i].size() <= n1-2) {
                    REP(x,ke[i].size()) {
                        int j = ke[i][x];
                        visited[j] = 1;
                    }
                    int u = -1, v = -1;
                    FOR(j,1,n) if (side[j] == 1 && !visited[j]) {
                        if (u == -1) u = j;
                        else if (v == -1) v = j;
                    }
                    if (u > 0 && v > 0) {
                        can = true;
                        side[i] = 1 - side[i];
                        side[u] = 1 - side[u];
                        side[v] = 1 - side[v];
                        res[i] = res[u] = res[v] = cur++;
                        break;
                    }
                    REP(x,ke[i].size()) {
                        int j = ke[i][x];
                        visited[j] = 0;
                    }
                }
                if (!can) {
                    int _ = 0;
                    FOR(i1,1,n) if (side[i1] == 1 && ke[i1].size() <= n0-2)
                    if (!can) {
                        int __ = 0;
                        FOR(i2,i1+1,n) if (side[i2] == 1 && ke[i2].size() <= n0-2) {
                            __++; if (__ == 5) break;
                            REP(x,ke[i1].size()) visited[ke[i1][x]] = 1;
                            REP(x,ke[i2].size()) visited[ke[i2][x]] += 2;
                            
                            int j1 = -1, j2 = -1, j3 = -1, j4 = -1;
                            FOR(j,1,n) if (side[j] == 0) if (visited[j] & 1) if (visited[j] < 2) {
                                if (j3 < 0) j3 = j;
                                else if (j4 < 0) j4 = j;
                            }
                            FOR(j,1,n) if (side[j] == 0) if (visited[j] >= 2) if ((visited[j] & 1) == 0) {
                                if (j1 < 0) j1 = j;
                                else if (j2 < 0) j2 = j;
                            }
                            FOR(j,1,n) if (side[j] == 0) if (!visited[j]) {
                                if (j1 < 0) j1 = j;
                                else if (j2 < 0) j2 = j;
                                else if (j3 < 0) j3 = j;
                                else if (j4 < 0) j4 = j;
                            }
                            
                            if (j1 > 0 && j2 > 0 && j3 > 0 && j4 > 0) {
                                can = true;
                                res[i1] = res[j1] = res[j2] = cur++;
                                res[i2] = res[j3] = res[j4] = cur++;
                                side[i1] = 1 - side[i1];
                                side[i2] = 1 - side[i2];
                                side[j1] = 1 - side[j1];
                                side[j2] = 1 - side[j2];
                                side[j3] = 1 - side[j3];
                                side[j4] = 1 - side[j4];
                                break;
                            }
    
                            REP(x,ke[i1].size()) visited[ke[i1][x]] = 0;
                            REP(x,ke[i2].size()) visited[ke[i2][x]] = 0;
                        }
                        _++;
                        if (_ == 2) break;
                    }
                }
            }
        }
        if (!can) {
            puts("NO");
            continue;
        }
        puts("YES");
        int has = 0;
//        PR(res, n);
        REP(turn,2) {
            FOR(i,1,n) if (side[i] == turn && res[i] < 0) {
                res[i] = cur;
                has++;
                if (has == 3) {
                    cur++;
                    has = 0;
                }
            }
        }
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
    return 0;
}
