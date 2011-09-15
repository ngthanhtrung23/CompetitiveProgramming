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

int m, n;
char a[200][200];

bool empty(int row) {
    REP(j,n) if (a[row][j] == 'W') return false;
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d %d\n", &m, &n);
    REP(i,m) gets(a[i]);
    
    while (m > 0 && empty(m-1)) m--;
    
    int now = 0;
    int res = 0;
    REP(i,m) if (i % 2 == 0) {
        int ln = now;
        REP(j,n) if (a[i][j] == 'W') ln = max(ln, j);
        if (i < m-1) REP(j,n) if (a[i+1][j] == 'W') ln = max(ln, j);
        if (i < m-1) res++;
        res += ln - now;
        now = ln;
    }
    else {
        int nn = now;
        REP(j,n) if (a[i][j] == 'W') nn = min(nn, j);
        if (i < m-1) REP(j,n) if (a[i+1][j] == 'W') nn = min(nn, j);
        if (i < m-1) res++;
        res += now - nn;
        now = nn;
    }
    cout << res << endl;
    return 0;
}
