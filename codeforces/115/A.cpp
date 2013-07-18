#pragma comment(linker, "/STACK:16777216")
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
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

int n, a[2011], res, h[2011];
vector<int> ke[2011];

void dfs(int u, int now) {
    h[u] = now;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (h[v] == 0) dfs(v, now+1);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d", &a[i]);
        if (a[i] >= 0) ke[a[i]].PB(i);
    }
    FOR(i,1,n) if (a[i] < 0) {
        dfs(i, 1);
    }
    int res = 0;
    FOR(i,1,n) res = max(res, h[i]);
    cout << res << endl;
    return 0;
}
