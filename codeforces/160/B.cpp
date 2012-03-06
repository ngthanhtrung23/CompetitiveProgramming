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

int n;
char a[2][111];

bool can(int x, int y) {
    FOR(i,1,n)
        if (a[x][i] >= a[y][i]) return false;
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) scanf("%c", &a[0][i]);
        FOR(i,1,n) scanf("%c", &a[1][i]);
        sort(a[0] + 1, a[0] + n + 1);
        sort(a[1] + 1, a[1] + n + 1);
        if (can(0, 1) || can(1,0)) puts("YES");
        else puts("NO");
    }
    return 0;
}
