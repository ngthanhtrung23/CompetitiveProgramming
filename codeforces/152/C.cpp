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
const int BASE = 1000000007;

bool can[333];
char s[111][111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m; scanf("%d%d\n", &n, &m);
    REP(i,n) {
        gets(s[i]);
    }
    long long res = 1;
    REP(x,m) {
        int cnt = 0;
        memset(can, false, sizeof can);
        REP(i,n) can[s[i][x]] = true;
        FOR(c,'A','Z') if (can[c]) cnt++;
        res = (res * cnt) % BASE;
    }
    cout << res;
    return 0;
}
