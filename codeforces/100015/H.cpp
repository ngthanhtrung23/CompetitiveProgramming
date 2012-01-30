#include <iomanip>
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

char c[111], a[111][111], b[111][111];
int n;

bool can(int r) {
    FOR(i,1,n) {
        int l = strlen(a[i]);
        REP(x,l) {
            char cur;
            if (x <= r) cur = c[x];
            else cur = b[i][x - r - 1];
            if ((cur + a[i][x]) % 26 + 'A' != b[i][x]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        int save = 1;
        FOR(i,1,n) {
            scanf("%s%s", &a[i][0], &b[i][0]);
            if (strlen(a[i]) > strlen(a[save])) save = i;
        }
        int l = strlen(a[save]);
        REP(i,l) {
            c[i] = (b[save][i] - a[save][i]+26) % 26 + 'A';
        }
        bool ok = false;
        FOR(i,0,l-1) {
            if (can(i)) {
                ok = true;
                FOR(x,0,i) printf("%c", c[x]);
                puts("");
                break;
            }
        }
        if (!ok) puts("Impossible");
    }
    return 0;
}
