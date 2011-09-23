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

char c[5011][5011];

int f[5011], n;
bool found = false;

void dfs(int u) {
    if (found) return ;
    REP(v,n) if (c[u][v] == '1') {
        if (f[v] == -1) {
            f[v] = u;
            dfs(v);
        }
        if (found) return ;
        
        if (f[u] >= 0 && c[v][f[u]] == '1') {
            found = true;
            cout << f[u] + 1 << ' ' << u + 1 << ' ' << v + 1 << endl;
            return ;
        }
        
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d\n", &n);
    REP(i,n) gets(c[i]);
    
    memset(f, -1, sizeof f);
    
    REP(i,n) if (f[i] == -1) {
        f[i] = -2;
        dfs(i);
    }
    if (!found) puts("-1");
    return 0;
}
