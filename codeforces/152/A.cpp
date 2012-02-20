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
using namespace std;

const double PI = acos(-1.0);

char s[111][111];
bool can[111];
int m, n;

bool best(int i, int j) {
    int ln = 0;
    REP(ii,n) ln = max(ln, (int) s[ii][j]);
    return (s[i][j] == ln);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d\n", &n, &m);
    REP(i,n) gets(s[i]);
    
    REP(i,n) {
        bool ok = false;
        REP(j,m) if (best(i,j)) { ok = true; break; }
        can[i] = ok;
    }
    
    int res = 0;
    REP(i,n) if (can[i]) res++;
    cout << res;
    return 0;
}
