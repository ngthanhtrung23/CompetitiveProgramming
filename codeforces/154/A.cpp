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

bool mark[333][333];
int f[100111][333];
char s[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(s);
    int k; scanf("%d\n", &k);
    while (k--) {
        char a, b; scanf("%c%c\n", &a, &b);
        mark[a][b] = true;
        mark[b][a] = true;
//        cout << a << ' ' << b << endl;
    }
    int l = strlen(s);
    f[0][s[0]] = 1;
    FOR(i,1,l-1) {
        f[i][s[i]] = 1;
        FOR(prev,'a','z') {
            if (!mark[prev][s[i]]) {
                f[i][s[i]] = max(f[i][s[i]], f[i-1][prev] + 1);
            }
            f[i][prev] = max(f[i][prev], f[i-1][prev]);
        }
    }
    int res = 0;
    FOR(c,'a','z') res = max(res, f[l-1][c]);
    printf("%d\n", l-res);
    return 0;
}
