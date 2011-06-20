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

char a[10111], b[1000111];
int next[10111][300];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(a); gets(b);
    
    int n = strlen(a);
    memset(next, -1, sizeof next);
    FORD(i,n-1,0) {
        FOR(c,'a','z') next[i][c] = next[i+1][c];
        next[i][a[i]] = i;
    }
    int now = 0;
    int q = strlen(b), res = 1;
    REP(i,q) {
        int u = next[now][b[i]];
        if (u == -1) {
            res ++;
            u = next[0][b[i]];
            if (u == -1) {
                puts("-1");
                return 0;
            }
        }
        now = u + 1;
    }
    cout << res;
    return 0;
}
